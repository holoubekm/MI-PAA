set terminal png size 800,480 enhanced 



set xlabel "Poměr sumární váhy předmětů a kapacity batohu"
set ylabel "Celkový čas CPU pro 50 instancí (s)"
set y2label "Relativní chyba pro 50 instancí (%)"

# set xrange [0.5:2.75]
# set yrange [2:3]
# set y2range [0.0:0.25]
# set log y
set tics
set y2tics
set border
set key
set datafile separator "\t" 
set key autotitle columnhead
set output "output/ratio_aprox.png"
plot "output/ratio.out.txt" using 1:4 with lines axes x1y1, \
	"output/ratio.out.txt" using 1:5 with lines axes x1y2

unset y2tics
unset y2label
unset yrange
set output "output/ratio_bb.png"
plot "output/ratio.out.txt" using 1:2 with lines

set output "output/ratio_dyn.png"
plot "output/ratio.out.txt" using 1:3 with lines
