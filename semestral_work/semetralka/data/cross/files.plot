set terminal png size 640,480 enhanced 

#set xrange [10:35]
#set xrange [14:35]
#set log y

set datafile separator " "
set xlabel "Počet křížených jedinců (max 300)"
set ylabel "Průměrný čas CPU pro 500 instancí (s)"
set output "output.png"
plot "avg.dat" using 1:2 title "Záv. času CPU na poč. kříž." with lines axes x1y1

set ylabel "Průměrná kvalita řešení pro 500 instancí (s)"
set y2label "Průměrná generace prvního řešení (max 500)"
set y2tics
set output "output2.png"
plot "avg.dat" using 1:4 title "Záv. kvality řešení na poč. kříž." with lines axes x1y1, \
"avg.dat" using 1:3 title "Záv. prv. řešení na poč. kříž." with lines axes x1y2 
