
graphs:
	cd cross; \
	./files.sh
	cd instances; \
	./files.sh
	cd iterations; \
	./files.sh
	cd keepbest; \
	./files.sh
	cd keepworst; \
	./files.sh
	cd mutation; \
	./files.sh

remove_generated:
	find . -iname '*.png' -exec rm {} \;
	find . -iname '.avg_err.dat' -exec rm {} \;
	find . -iname 'avg_err.dat' -exec rm {} \;
	find . -iname '.avg_time.dat' -exec rm {} \;
	find . -iname 'avg_time.dat' -exec rm {} \;

remove_dat:
	find . -iname '*.dat' -exec rm {} \;