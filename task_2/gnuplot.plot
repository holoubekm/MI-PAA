set terminal png size 640,480 enhanced 


#set label "S" at graph 0.5,0.5 center
#set xrange [5:40]
#plot "avg_err.txt" using 1:2 title "\nZavislosti casu CPU\nna velikosti instance" with lines 

set xlabel "Velikost instance"

#set output "max_err.png"
#set ylabel "Maximální průměrná relativní chyba pro 50 instancí"
#set xrange [10:35]
#plot "max_err.txt" using 1:2 title "\nZávislost maximální relativní chyby\nna #velikosti instance" with lines 

#set output "avg_err.png"
#set ylabel "Průměrná relativní chyba pro 50 instancí"
#set xrange [10:35]
#plot "avg_err.txt" using 1:2 title "\nZávislost relativní chyby\nna velikosti #instance" with lines 

set output "dyn_time.png"
set ylabel "Celkový čas CPU pro 50 instancí (s)"
set xrange [14:35]
#set log y
plot "dyn_time.txt" using 1:2 title "\nZávislost času CPU\nna velikosti instance" with lines 

set output "eps_time.png"
set ylabel "Celkový čas CPU pro 50 instancí (s)\nv závislosti na zvolené přesnosti"
#set xrange [14:35]
#set log y
plot "eps_time.txt" using 1:2 title "\nZávislost času CPU\nna velikosti instance" with lines 

set output "approx_time.png"
set ylabel "Celkový čas CPU pro 50 instancí (s)"
set xrange [4:35]
set log y
plot "approx_time.txt" using 1:2 title "\nZávislost času CPU\nna velikosti instance" with lines 

set output "optimal_time.png"
set ylabel "Celkový čas CPU pro 50 instancí (s)"
set xrange [28:35]
plot "optimal_time.txt" using 1:2 title "\nZávislost času CPU\nna velikosti instance" with lines 

set output "optimal_time_log.png"
set ylabel "Celkový čas CPU pro 50 instancí (s)\nlogaritmické měřítko"
set xrange [4:35]
set log y
plot "optimal_time.txt" using 1:2 title "\nZávislost času CPU\nna velikosti instance" with lines 
