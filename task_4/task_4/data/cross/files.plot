set terminal png size 640,480 enhanced 

#set xrange [10:35]
#set xrange [14:35]
#set log y

set xlabel "Počet křížení v každé generaci"
set output "output.png"
set ylabel "Průměrný čas CPU pro 50 instancí (s)"
set y2label "Průměrná relativní chyba (%) pro 50 instancí"
set y2tics
plot "avg_time.dat" using 1:2 title "Záv. času CPU na p. kříž." with lines axes x1y1, \
"avg_err.dat" using 1:2 title "Záv. rel. chyby na p. kříž." with lines axes x1y2 