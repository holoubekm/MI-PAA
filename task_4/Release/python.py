#!/bin/python

import re

gens = {}

with open("OUTPUT.TXT") as iii:
	for line in iii.readlines():
		line = line.strip()
		m = re.match('Gen: (\d+), Error: (\d+\.\d+)', line)
		if m is not None:
			gen = m.groups()[0]
			val = m.groups()[1]

			if not gen in gens:
				gens[gen] = { 'cnt': 0, 'val': 0.0 }
			gens[gen]['cnt'] += 1
			gens[gen]['val'] += float(val)

keys = sorted([int(x) for x in gens.keys()])
for key in keys:
	key = str(key)
	cnt = gens[key]['cnt']
	val = gens[key]['val']
	print(key + "\t" + str(val / cnt))
