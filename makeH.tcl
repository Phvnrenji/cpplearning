#!/bin/sh
# the next line restarts using wish \
exec wish "$0" "$@"

#
# cp -f ~/tcl/makeH.tcl ~/pub/tcl
#
# Recent changes
##  scrollbars on lower canvas
##  extra scrolling canvases that show the row sums and column sums only
##  hover on an entry highlights all its relatives and cousins
##  Hover on a row highlights all the other entries/rows in other rows
##         that that row has washing line associations with. 
##  Temporarily focus attention on one "exhaustive tile"

# To do
##  Provide a way to commit to making tow particular columns be in
##      an edge together, but with the row as yet unspecified.
##  Add comments, annotations
##  Identify Two Edges
##  Merge Two Columns
##  Reorder columns or rows
##  Create standard structures in given locations;
##    e.g. add a dodec or a monodec to a given row.
##  read from file
##  Highlight one row in the lower matrix
##  vary M and N
##  introduce alternative colours to white to help the planner.
##  extra column markers to make it easy to count cols and rows
##  Hover on a column highlights entries which would help in that 
##         column's overlap contributions
##  Undo.
##  As well as toggle, have a WIPE mode and a write-only mode

#
# set these two flags to 1 to get a stand-alone version
# as used by me; leave them at 0 to get plug-in netscape
# compatible version:
#
global verbose ; set verbose 0
global ownwindow ; set ownwindow 1
global version ; set version 1.1
global pinkish ; set pinkish "#ff00ff"

frame .tsp
pack  .tsp
set w .tsp
set top .
if {$ownwindow>=1} {
    wm geometry . +10+10
    wm title . "Make your own parity check matrix"
    wm iconname . "makeH"
    puts "Make your own parity check matrix"
    puts "---------------------------------"
    puts " <1> to create or destroy edges"
    puts " <3> to move the viewpoint in either canvas"
    puts " Row and column counters show whether you have "
    puts "      the desired row and column weights"
    puts " <3> to highlight one row of the matrix and its cousins"
    puts " R   to reset the colours"
    puts " After <3>, the white and cyan counters at the top report"
    puts "       the number of associated rows, and how many of them have weights other than 2"
    puts " The overlap matrix (bottom left) reports on overlaps between rows"
    puts " Print - writes the matrix to A.txt"
    puts " "
    puts "BUGS"
    puts "----"
    puts " the M and N controls do nothing" 
}
bind . <Control-C> {destroy .}
bind . <Control-c> {destroy .}
set colone [frame .tsp.colone]
set toprow [frame .tsp.toprow]
pack $toprow -side top
pack $colone -side left


frame $w.buttons
pack $w.buttons -in $toprow  -side right -fill x -pady 2m -padx 2m
button $w.buttons.dismiss -text Dismiss -command "destroy $top" -borderwidth 1  -padx 0 -pady 0 
button $w.buttons.print -text Print -command "printA"  -borderwidth 1  -padx 0 -pady 0 
pack $w.buttons.print $w.buttons.dismiss   -side right -expand 1

global font ; set font "Courier 9"
global bigfont ; set bigfont "Courier 11"
global x
global state
set state(1) "white"
set state(0) "black"

# display current row and col
global TheRow ; set TheRow 0
global TheCol ; set TheCol 0
label $w.theRow  -width 3 -justify left -text "" -textvariable TheRow  -background  "#ffffee"  -anchor nw  -font $bigfont
label $w.theCol  -width 3 -justify left -text "" -textvariable TheCol  -background  "#ffffee"  -anchor nw  -font $bigfont
global Energy ; set Energy 0
label $w.energyl -width 15 -justify left -text "Associated rows:" -background pink1 -anchor nw  -font $bigfont
label $w.energy -width 3 -justify left -text "" -textvariable Energy -background  white  -anchor nw  -font $bigfont
global Happy ; set Happy ""
label $w.happy -width 3 -justify left -text "" -textvariable Happy -background cyan -anchor nw  -font $bigfont
pack   $w.theRow  $w.theCol   -in $toprow -side left  -padx 3
pack $w.energyl $w.energy -in $toprow -side left 
pack $w.happy -in $toprow -side left 


# make a frame called l within frame controls, and associate these buttons 
# with an integer called L
proc adjustableInteger { w controls l Lname Lstring } {
    frame $w.$l 
    pack $w.$l -in $controls -side left  -pady 2  -padx 2 -anchor w
    button $w.$l.l -text "$Lstring:" -padx 0 -pady 0 -borderwidth 1 -command {}
    button $w.$l.up -text ">" -padx 0 -pady 0 -borderwidth 1 -command "incr $Lname"
    button $w.$l.dn -text "<" -padx 0 -pady 0 -borderwidth 1 -command "incr $Lname -1"
    bind  $w.$l.up  <3> "$w.$l.dn invoke"
    bind  $w.$l.dn  <3> "$w.$l.up invoke"
    entry $w.$l.n -textvariable $Lname -width 3 -borderwidth 1
    pack $w.$l.l $w.$l.dn $w.$l.up $w.$l.n -in $w.$l -side left
}

global M 
global N 
global J K
adjustableInteger $toprow $toprow "j" J j
set J 4
adjustableInteger $toprow $toprow "k" K k
set K 10
adjustableInteger $toprow $toprow "m" M M
adjustableInteger $toprow $toprow "n" N N
set M 9 ;  set N 17
set M 90 ; set N 180
set M 149 ; set N 300

# rectangle sizes (updated below)
global recdx ; set recdx 8
global recdy ; set recdy $recdx
global recwidth ; set recwidth 8 
global recheight ; set recheight $recwidth
set height [expr ($M+6)*$recdx]
set width [expr ($N+6)*$recdy]
global inferenceblue ; set  inferenceblue "#005544"
global lightinferenceblue ; set  lightinferenceblue "#009977"
global xn
global A

# passes the scroll commnad to TWO canvases
proc vertical_echo { args } {
    global c cvfrag
    set s [concat   $c yview [concat [split $args]]]
#puts $s
 eval $s
    set s [concat   $cvfrag yview [concat [split $args]]]
 eval $s
#    $cvfrag yview $args split?
}

# passes the scroll commnad to TWO canvases
proc horizontal_echo { args } {
    global c chfrag
    set s [concat   $c xview [concat [split $args]]]
 eval $s
    set s [concat   $chfrag xview [concat [split $args]]]
 eval $s
}

# a frame to put the canvas in with its scrollers
frame $w.grid
set widthmax 850
set heightmax 450
set scrollwidth 7
set c $w.c
# a little canvas fragment
set cvfrag $w.cvfrag
set chfrag $w.chfrag
# c is the canvas
scrollbar $w.hscroll -orient horiz -command "horizontal_echo" -width $scrollwidth -borderwidth 1 
scrollbar $w.vscroll -command "vertical_echo" -width $scrollwidth -borderwidth 1 
canvas $c -relief sunken -borderwidth 1 -width $widthmax -height $heightmax -background black \
 -scrollregion [list -20 -20 $width $height] \
	-xscrollcommand "$w.hscroll set" \
	-yscrollcommand "$w.vscroll set"
# a little canvas fragment
canvas $cvfrag -relief sunken -borderwidth 1 -width 17 -height $heightmax \
 -background black \
 -scrollregion [list 0 -20 17 $height] \
	-yscrollcommand "$w.vscroll set"
canvas $chfrag -relief sunken -borderwidth 1 -width $widthmax -height 16 \
 -background black \
 -scrollregion [list -20 0 $width 15] \
	-xscrollcommand "$w.hscroll set"

# Recolor button
button $w.recolor -text R -command "revertRow $c"  -borderwidth 1  -padx 0 -pady 0 
# pack comes below
grid rowconfig    $w.grid 0 -weight 1 -minsize 0
grid columnconfig $w.grid 0 -weight 1 -minsize 0

grid $c -padx 0 -in $w.grid -pady 0 \
    -row 0 -column 0 -rowspan 1 -columnspan 1 -sticky news
grid $w.vscroll -in $w.grid -padx 0 -pady 0 \
    -row 0 -column 2 -rowspan 1 -columnspan 1 -sticky news
grid $cvfrag -in $w.grid -padx 0 -pady 0 \
    -row 0 -column 1 -rowspan 1 -columnspan 1 -sticky news
grid $chfrag -in $w.grid -padx 0 -pady 0 \
    -row 1 -column 0 -rowspan 1 -columnspan 1 -sticky news
grid $w.hscroll -in $w.grid -padx 0 -pady 0 \
    -row 2 -column 0 -rowspan 1 -columnspan 1 -sticky news
grid $w.recolor -in $w.grid -padx 0 -pady 0 \
    -row 1 -column 1 -rowspan 2 -columnspan 2 -sticky news
bind $c <3> "$c scan mark %x %y; $chfrag scan mark %x %y; $cvfrag scan mark %x %y"
bind $c <B3-Motion> "$c scan dragto %x %y; $chfrag scan dragto %x %y; $cvfrag scan dragto %x %y"

bind $cvfrag <3> "$c scan mark %x %y; $chfrag scan mark %x %y; $cvfrag scan mark %x %y"
bind $cvfrag <B3-Motion> "$c scan dragto %x %y; $chfrag scan dragto %x %y; $cvfrag scan dragto %x %y"

bind $chfrag <3> "$c scan mark %x %y; $chfrag scan mark %x %y; $cvfrag scan mark %x %y"
bind $chfrag <B3-Motion> "$c scan dragto %x %y; $chfrag scan dragto %x %y; $cvfrag scan dragto %x %y"


set bg [lindex [$c config -bg] 4]
set topy 0
set ii 1
global row column
global dullcolor rowweight
set dullcolor blue
for {set i 1 } {$i <= $M} {incr i} {
    set y [expr {$recdy * ($i+1) }]
    for {set j 1} {$j <= $N} {incr j} {
	set x [expr {$recdx*($j+1)}]
	set xn($ii) 0
	set A($i,$j) 0
	set item [$c create rect \
		${x} ${y} [expr $x+$recwidth] [expr $y+$recheight] \
		-width 1 -outline $dullcolor -fill $state($xn($ii)) \
		-tags [list row$i column$j  node$i$j nd$ii]]
	$c addtag node withtag $item
	set row($ii) $i
	set column($ii) $j
	
	if {$verbose>1} {	puts "row($ii) = $row($ii), column($ii) = $column($ii)" }
	incr ii
    }
# row label location
    set x [expr {$recdx*(-1)}]
    set item [$c create text ${x} ${y} -anchor n -justify right \
	    -text "$i" -font $font -tags label -fill green1]
# record the row weights at the side
    set rowweight($i) 0
    set x [expr {$recdx * (1)}]
    set item [$c create text ${x} ${y}  -anchor n -justify right \
	    -text "$rowweight($i)" -font $font -tags [list weight roww$i] -fill blue]
    set item [$cvfrag create text ${x} ${y}  -anchor n -justify right \
	    -text "$rowweight($i)" -font $font -tags [list weight roww$i] -fill blue]
    set x [expr {$recdx * ($N+4)}]
    set item [$c create text ${x} ${y}  -anchor n -justify right \
	    -text "$rowweight($i)" -font $font -tags [list weight roww$i] -fill blue]
# 
}
# column labels
for {set j 1} {$j <= $N} {incr j} {
    set x [expr {$recdx*($j+1.35)}]
# location for label of column
    set y [expr {$recdy * (-1)}]
    set item [$c create text ${x} ${y}  -anchor w -justify right \
	    -text "$j" -font $font -tags label -fill green]
# record the col weights at bottom
    set weight($j) 0
    set y [expr {$recdy * ($M+3)}]
    set item [$c create text ${x} ${y}  -anchor w -justify right \
	    -text "$weight($j)" -font $font -tags [list weight w$j] -fill blue]
    set y [expr {$recdy * (1)}]
    set item [$c create text ${x} ${y}  -anchor w -justify right \
	    -text "$weight($j)" -font $font -tags [list weight w$j] -fill blue]
    set item [$chfrag create text ${x} ${y}  -anchor w -justify right \
	    -text "$weight($j)" -font $font -tags [list weight w$j] -fill blue]
}
#######################################
# make distance canvas
#########################################
# rectangle sizes (see above also)
global recdx ; set recdx 6
global recdy ; set recdy $recdx
global recwidth ; set recwidth 6 
global recheight ; set recheight $recwidth
set height [expr ($M+3)*$recdx]
##################
set cd $w.cd
frame $w.dgrid
set widthmax 400
set heightmax 200

scrollbar $w.dhscroll -orient horiz -command "$cd xview" -width $scrollwidth -borderwidth 1 
scrollbar $w.dvscroll -command "$cd yview" -width $scrollwidth -borderwidth 1 
canvas $cd -relief sunken -borderwidth 2  -width $widthmax -height $heightmax  -background  black \
 -scrollregion [list -20 -20 $height $height] \
	-xscrollcommand "$w.dhscroll set" \
	-yscrollcommand "$w.dvscroll set"


# pack comes below
grid rowconfig    $w.dgrid 0 -weight 1 -minsize 0
grid columnconfig $w.dgrid 0 -weight 1 -minsize 0

grid $cd -padx 1 -in $w.dgrid -pady 1 \
    -row 0 -column 0 -rowspan 1 -columnspan 1 -sticky news
grid $w.dvscroll -in $w.dgrid -padx 1 -pady 1 \
    -row 0 -column 2 -rowspan 1 -columnspan 1 -sticky news
grid $w.dhscroll -in $w.dgrid -padx 1 -pady 1 \
    -row 2 -column 0 -rowspan 1 -columnspan 1 -sticky news
bind $cd <3> "$cd scan mark %x %y"
bind $cd <B3-Motion> "$cd scan dragto %x %y"


set ii 1
for {set i 1 } {$i <= $M} {incr i} {
    set x [expr {$recdx*($i+1)}]
    for {set j 1} {$j <= $M} {incr j} {
	set y [expr {$recdy * ($j+1)}]
#overlap
	set d($i,$j) [expr 0]
	if {$i==$j} {
	    set s "" 
	} else {
	    set s [expr $d($i,$j)]
	    set item [$cd create text ${x} ${y} \
		   -font $font -text "$s" -tags [list distance row$i  row$j d$i,$j d$ii] -fill $dullcolor]
	    incr ii
	    $cd addtag overlap withtag $item
	}
    }
    set y [expr {$recdx*0}]
    set item [$cd create text ${x} ${y} \
	    -text  $i  -font $font -tags label -fill green1]
    set item [$cd create text ${y} ${x} \
	    -text  $i  -font $font -tags label -fill green1]
}

# pack $c $cd -side top -in $colone
# set bgw [lindex [$cw config -bg] 4]
pack $w.grid $w.dgrid -expand yes -fill both -padx 1 -pady 1 -in $colone -side top

# revert main canvas to white by clicking in other canvas.
# bind $cd <3> " revertRow $c "

$c bind node <3> "highlightRow $c"
$c bind node <1> "toggleNode $c"
$c bind node <B1-Enter> "enterNode $c $cd ; toggleNode $c"
$c bind node <Shift-Enter> "enterNode $c $cd ; toggleNode $c"
$c bind node <Control-Enter> "enterNode $c $cd ; toggleNode $c"
$c bind node <Any-Enter> "enterNode $c $cd"
$c bind node <Any-Leave> "itemLeave"

$cd bind distance <Any-Enter> "enterDistance $cd $c"
$cd bind distance <Any-Leave> "itemLeave"

# from plot.tcl

# Utility procedures for highlighting the item under the pointer:

proc enterDistance {cd c} {
    global restoreCmd 
    global verbose  dullcolor
    set rememberdistancecolor [lindex [$cd itemconfig current -fill] 4]


    $cd  itemconfig current -fill green
# find weights that use this distance
    set nowthen [$cd gettags current]
#    puts $nowthen
# do a search for all tags in canvas c that match the current rows
    set where [lsearch -regexp $nowthen row]
    set myda [lindex $nowthen $where]
    set mydb [lindex $nowthen [expr $where+1]]
    if {$verbose>=1} {
	puts "$myda $mydb"
    }
    global TheRow  TheCol
    regsub "row"  $myda "" TheRow
    regsub "row"  $mydb "" TheCol

# highlight two rows in canvas c
    $c itemconfig $myda  -outline cyan
    $c itemconfig  $mydb -outline cyan
    set restoreCmd "$cd itemconfig current -fill $rememberdistancecolor ;     $c itemconfig $myda -outline $dullcolor;     $c itemconfig  $mydb -outline $dullcolor"
}

proc enterNode {c cd} {
    global verbose pinkish dullcolor
    global restoreCmd 

    set nowthen [$c gettags current]
# find the nd-ii tag and the row and column
    set rowtag [lindex $nowthen [lsearch -regexp $nowthen row]]
    set columntag [lindex $nowthen [lsearch -regexp $nowthen column]]
#
# this is the node's own tag
    set myn [lindex $nowthen [lsearch -regexp $nowthen nd]]
    if {$verbose>=1} {
	puts "$myn"
    }
    regsub  "nd" $myn "" ii
# to highlight entries in the distance/overlap table
#    $cd itemconfig $rowtag -fill $pinkish

    global TheRow  TheCol
    regsub "row"  $rowtag "" TheRow
    regsub "column"  $columntag "" TheCol
    
    $c itemconfig $rowtag -outline $pinkish
    $c itemconfig $columntag -outline green
    $c  itemconfig current -outline skyblue2
    set restoreCmd "$c itemconfig current -outline $dullcolor;  $c itemconfig $rowtag -outline $dullcolor ;     $c itemconfig $columntag -outline $dullcolor "
}

proc toggleNode {c} {
    global restoreCmd 
    global verbose
    global state xn A row column

    set nowthen [$c gettags current]

    set myn [lindex $nowthen [lsearch -regexp $nowthen nd]]
    if {$verbose>=1} {
	puts "$myn"
    }
    regsub  "nd" $myn "" ii
    set xn($ii) [expr 1-$xn($ii)]
    set A($row($ii),$column($ii)) [expr $xn($ii)]
    if {$verbose>2} {
	puts "SET $row($ii) $column($ii) $A($row($ii),$column($ii))"
    }
    $c  itemconfig current -fill $state($xn($ii))
    if { $A($row($ii),$column($ii)) > 0 } {
	$c addtag active withtag current
    } else {
# delete tag "active"
	$c dtag current  active
    }
    # find change in energy
    find_energy $ii
}

proc revertRow {c} {
# first set all active ones to a different colour to cancel out earlier selections
# restore original colours
global dullcolor
    $c  itemconfig  active  -fill white
    $c itemconfig node -outline $dullcolor
}
proc highlightRow {c} {
    global verbose M
    global state xn A row column lightinferenceblue dullcolor

    # remove highlights as in   revertRow $c     
      $c itemconfig node -outline $dullcolor
# first set all active ones to a different colour to cancel out earlier selections
    $c  itemconfig  active  -fill $lightinferenceblue

    set nowthen [$c gettags current]
# find the node number
    set myn [lindex $nowthen [lsearch -regexp $nowthen nd]]

# find what row we are in
    set myr [lindex $nowthen [lsearch -regexp $nowthen row]]
    if {$verbose>=1} {
	puts "$myr"
    }
    regsub "row" $myr "" thisrow
# prepare an array for row counting
    for { set rr 1 } { $rr <= $M  } { incr rr } { 
	set count($rr) 0 
    }
# find the columns of all the people in my row
#    1. find all items in my row that are active
    set itemlist [$c find withtag "active && $myr" ]
    foreach it $itemlist {
	set colsearch [$c gettags $it]
#	puts $colsearch
	set myc [lindex $colsearch [lsearch -regexp $colsearch col]]
#	puts "extracted column tags:"	puts $cols
	$c  itemconfig  "active && $myc" -fill white
# while we are here lets try to automate the spotting
# of happy solutions
	set whitelist [$c find withtag "active && $myc"]
	foreach whiteguy $whitelist {
	    set otherrowsearch [$c gettags $whiteguy]
	    set otherrow [lindex $otherrowsearch [lsearch -regexp $otherrowsearch row]]
	    regsub "row" $otherrow "" rr
	    incr count($rr)
	}
    }
    # this searches for a conjunction of two tags
    $c  itemconfig  "active && $myr" -fill yellow
    set happy 0
    set unhappy 0
    for { set rr 1 } { $rr <= $M  } { incr rr } { 
	if { ($count($rr) > 0)  } {
	    if { $rr == $thisrow } {
	    } elseif { $count($rr) != 2 } {
		if {$verbose>1} {
		    puts "Row $rr: count is $count($rr)" 
		}
		# highlight the bad rows
		$c itemconfig row$rr -outline cyan
		incr unhappy
	    } else {
		incr happy
	    }
	}
    }
    set total [expr ($unhappy+$happy)]
    if {$verbose>1} {
	puts "And $happy happy rows of $total other than the source row, $myr"
    }
    global Happy; set Happy $unhappy
    global Energy; set Energy $total
}

proc find_energy { ii } {
# visit every other node in this column.
    global verbose column M d  xn A  row column cd weight rowweight J c K
    global chfrag cvfrag
    set thiscol $column($ii)
   set thisrow $row($ii) 
    if {$verbose>=2} {     puts "ii = $ii, row = $thisrow, column = $thiscol" }
#    $c itemconfig col$ii
    set activation 0

    if {$verbose >1 } {    puts "finde"  }

    if { $xn($ii) } {
	set sign 1
    } else {
	set sign -1
    }
    incr weight($thiscol) $sign
		if { $weight($thiscol)==$J  } {
		    set		    colorstring "red"
		} else {
		    set		    colorstring "cyan"
		}
    $c itemconfigure w$thiscol -text $weight($thiscol) -fill $colorstring
    $chfrag itemconfigure w$thiscol -text $weight($thiscol) -fill $colorstring
    incr rowweight($thisrow) $sign
		if { $rowweight($thisrow)==$K  } {
		    set		    colorstring "red"
		} else {
		    set		    colorstring "cyan"
		}
    $c itemconfigure roww$thisrow -text $rowweight($thisrow) -fill $colorstring
    $cvfrag itemconfigure roww$thisrow -text $rowweight($thisrow) -fill $colorstring
    for {set i 1 } {$i <= $M} {incr i} {
	if {$i != $thisrow} {
	    if {$verbose>2} {puts ", $i $thiscol $A($i,$thiscol)" }
	    if {$A($i,$thiscol)} {
		if {$verbose>10} {puts ", $i $thiscol $A($i,$thiscol), changing by $signw $d($i,$thisrow) $d($thisrow,$i)" }

		incr d($i,$thisrow) $sign
		incr d($thisrow,$i) $sign
		set answer $d($i,$thisrow)
		if { [expr  !($answer%2)] } {
#		    puts "$answer is even"
		    set		    colorstring "red"
		} else {
#		    puts "$answer not even"
		    set		    colorstring "cyan"
		}
		if { $answer>2 } { set colorstring "yellow" }
		$cd itemconfigure d$i,$thisrow -text $answer -fill $colorstring
		$cd itemconfigure d$thisrow,$i -text $answer -fill $colorstring
		if {$verbose>10} {puts " -> $d($i,$thisrow)" }

	    }
	} else {
#	    puts "."
	}
    }

}

proc itemLeave { } {
    global restoreCmd

    eval $restoreCmd
}
#####################################################################

# subroutine for positioning magnification in response to the horizontal coord
proc hpositionscale {w s} {
    $w.scale set [expr $s*0.01]

    $w.c coords poly $s 15 $s 35 [expr $s+20] 35 [expr $s+20] 15
    $w.c coords line $s 15 $s 35 [expr $s+20] 35 [expr $s+20] 15
}

global file
set file A.txt

proc printA { } {
    global  A M N 
    global file 
    set fp [open $file w]
    for {set i 1 } {$i <= $M} {incr i} {
	for {set j 1} {$j <= $N} {incr j} {
	    puts -nonewline $fp $A($i,$j)
	}
	puts  $fp ""

    }
    close $fp
}

