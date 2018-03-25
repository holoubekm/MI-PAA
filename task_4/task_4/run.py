#!/bin/python3

import sys
import os
import subprocess
from subprocess import call

BUILD="Release"

def run(args):
	ARGS = " " +  str(args['input'])
	ARGS += " " + str(args['solution'])
	ARGS += " " + str(args['instances'])
	ARGS += " " + str(args['iterations'])
	ARGS += " " + str(args['keepBest'])
	ARGS += " " + str(args['keepWorst'])
	ARGS += " " + str(args['cross'])
	ARGS += " " + str(args['mutationFactor'])
	x=subprocess.Popen(BUILD+"/task_4 " + ARGS, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)

	line = x.stdout.readline()
	while line:
		ret = line.decode('utf-8')
		line = x.stdout.readline()
		yield ret
	x.wait()

subprocess.call(["make", "-C", BUILD])

def testInstances():
	insts = [25, 50, 100, 150, 300, 600]
	for inst in insts:
		args = {
			'input': 'knap_500.inst.dat',
			'solution': 'knap_500.sol.dat',
			'instances': inst,
			'iterations': 500,
			'keepBest': int(0.10 * inst),
			'keepWorst': int(0.07 * inst),
			'cross': int(0.07 * inst),
			'mutationFactor': 0.05 }
		fname = ""
		for key in ['instances', 'iterations', 'keepBest', 'keepWorst', 'cross', 'mutationFactor']:
			fname += str(args[key]) + "_"
		fname = "data/instances/" + fname.strip() + ".dat"
		with open(fname, 'w') as output:
			for line in run(args):
				output.write(line)

def testIterations():
	ites = [50, 100, 250, 750, 1500, 3000, 6000]
	for ite in ites:
		args = {
			'input': 'knap_500.inst.dat',
			'solution': 'knap_500.sol.dat',
			'instances': 300,
			'iterations': ite,
			'keepBest': int(0.10 * 300),
			'keepWorst': int(0.07 * 300),
			'cross': int(0.07 * 300),
			'mutationFactor': 0.05 }
		fname = ""
		for key in ['instances', 'iterations', 'keepBest', 'keepWorst', 'cross', 'mutationFactor']:
			fname += str(args[key]) + "_"
		fname = "data/iterations/" + fname.strip() + ".dat"
		with open(fname, 'w') as output:
			for line in run(args):
				output.write(line)

def testKeepBest():
	keepBests = [0.05, 0.10, 0.15, 0.20, 0.30, 0.40, 0.50]
	for keepBest in keepBests:
		args = {
			'input': 'knap_500.inst.dat',
			'solution': 'knap_500.sol.dat',
			'instances': 300,
			'iterations': 1500,
			'keepBest': int(keepBest * 300),
			'keepWorst': int(0.07 * 300),
			'cross': int(0.07 * 300),
			'mutationFactor': 0.05 }
		fname = ""
		for key in ['instances', 'iterations', 'keepBest', 'keepWorst', 'cross', 'mutationFactor']:
			fname += str(args[key]) + "_"
		fname = "data/keepbest/" + fname.strip() + ".dat"
		with open(fname, 'w') as output:
			for line in run(args):
				output.write(line)

def testKeepWorst():
	keepWorsts = [0.05, 0.10, 0.15, 0.20, 0.30, 0.40, 0.50]
	for keepWorst in keepWorsts:
		args = {
			'input': 'knap_500.inst.dat',
			'solution': 'knap_500.sol.dat',
			'instances': 300,
			'iterations': 1500,
			'keepBest': int(0.1 * 300),
			'keepWorst': int(keepWorst * 300),
			'cross': int(0.07 * 300),
			'mutationFactor': 0.05 }
		fname = ""
		for key in ['instances', 'iterations', 'keepBest', 'keepWorst', 'cross', 'mutationFactor']:
			fname += str(args[key]) + "_"
		fname = "data/keepworst/" + fname.strip() + ".dat"
		with open(fname, 'w') as output:
			for line in run(args):
				output.write(line)

def testCross():
	crosses = [0.05, 0.10, 0.15, 0.20, 0.30, 0.40, 0.50]
	for cross in crosses:
		args = {
			'input': 'knap_500.inst.dat',
			'solution': 'knap_500.sol.dat',
			'instances': 300,
			'iterations': 1500,
			'keepBest': int(0.1 * 300),
			'keepWorst': int(0.07 * 300),
			'cross': int(cross * 300),
			'mutationFactor': 0.05 }
		fname = ""
		for key in ['instances', 'iterations', 'keepBest', 'keepWorst', 'cross', 'mutationFactor']:
			fname += str(args[key]) + "_"
		fname = "data/cross/" + fname.strip() + ".dat"
		with open(fname, 'w') as output:
			for line in run(args):
				output.write(line)

def testMutation():
	mutations = [0.05, 0.10, 0.15, 0.20, 0.30, 0.40, 0.50]
	for mutation in mutations:
		args = {
			'input': 'knap_500.inst.dat',
			'solution': 'knap_500.sol.dat',
			'instances': 300,
			'iterations': 1500,
			'keepBest': int(0.1 * 300),
			'keepWorst': int(0.07 * 300),
			'cross': int(0.07 * 300),
			'mutationFactor': mutation }
		fname = ""
		for key in ['instances', 'iterations', 'keepBest', 'keepWorst', 'cross', 'mutationFactor']:
			fname += str(args[key]) + "_"
		fname = "data/mutation/" + fname.strip() + ".dat"
		with open(fname, 'w') as output:
			for line in run(args):
				output.write(line)


testInstances()
testIterations()
testKeepBest()
testKeepWorst()
testCross()
testMutation()