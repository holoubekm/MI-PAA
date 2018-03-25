#!/bin/python3

import sys
import os
import subprocess
from subprocess import call

BUILD="Release"

def run(args):
	ARGS  = " " + str(args['instances'])
	ARGS += " " + str(args['iterations'])
	ARGS += " " + str(args['keepBest'])
	ARGS += " " + str(args['keepWorst'])
	ARGS += " " + str(args['cross'])
	ARGS += " " + str(args['mutationFactor'])
	ARGS += " " + str(args['maxClauses'])
	x=subprocess.Popen(BUILD+"/semestralka " + ARGS, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)

	line = x.stdout.readline()
	while line:
		ret = line.decode('utf-8')
		line = x.stdout.readline()
		yield ret
	x.wait()

subprocess.call(["make"], cwd=BUILD)

def testInstances():
	print('Testing phase: Instances')
	insts = [25, 50, 100, 150, 300, 600]
	for inst in insts:
		args = {
			'instances': inst,
			'iterations': 500,
			'keepBest': int(0.10 * inst),
			'keepWorst': int(0.07 * inst),
			'cross': int(0.07 * inst),
			'mutationFactor': 0.001,
			'maxClauses': 40 }
		fname = ""
		for key in ['instances', 'iterations', 'keepBest', 'keepWorst', 'cross', 'mutationFactor']:
			fname += str(args[key]) + "_"
		fname = "data/instances/" + fname.strip() + ".dat"
		with open(fname, 'w') as output:
			for line in run(args):
				output.write(line)

def testIterations():
	print('Testing phase: Iterations')
	ites = [50, 100, 200, 400, 800, 1600]
	for ite in ites:
		args = {
			'instances': 300,
			'iterations': ite,
			'keepBest': int(0.10 * 300),
			'keepWorst': int(0.07 * 300),
			'cross': int(0.07 * 300),
			'mutationFactor': 0.001,
			'maxClauses': 40 }
		fname = ""
		for key in ['instances', 'iterations', 'keepBest', 'keepWorst', 'cross', 'mutationFactor']:
			fname += str(args[key]) + "_"
		fname = "data/iterations/" + fname.strip() + ".dat"
		with open(fname, 'w') as output:
			for line in run(args):
				output.write(line)

def testKeepBest():
	print('Testing phase: KeepBest')
	keepBests = [0.005, 0.05, 0.10, 0.15, 0.20, 0.30, 0.50]
	for keepBest in keepBests:
		args = {
			'instances': 300,
			'iterations': 500,
			'keepBest': int(keepBest * 300),
			'keepWorst': int(0.07 * 300),
			'cross': int(0.07 * 300),
			'mutationFactor': 0.001,
			'maxClauses': 40 }
		fname = ""
		for key in ['instances', 'iterations', 'keepBest', 'keepWorst', 'cross', 'mutationFactor']:
			fname += str(args[key]) + "_"
		fname = "data/keepbest/" + fname.strip() + ".dat"
		with open(fname, 'w') as output:
			for line in run(args):
				output.write(line)

def testKeepWorst():
	print('Testing phase: KeepWorst')
	keepWorsts = [0.005, 0.05, 0.10, 0.15, 0.20, 0.30, 0.50]
	for keepWorst in keepWorsts:
		args = {
			'instances': 300,
			'iterations': 500,
			'keepBest': int(0.1 * 300),
			'keepWorst': int(keepWorst * 300),
			'cross': int(0.07 * 300),
			'mutationFactor': 0.001,
			'maxClauses': 40 }
		fname = ""
		for key in ['instances', 'iterations', 'keepBest', 'keepWorst', 'cross', 'mutationFactor']:
			fname += str(args[key]) + "_"
		fname = "data/keepworst/" + fname.strip() + ".dat"
		with open(fname, 'w') as output:
			for line in run(args):
				output.write(line)

def testCross():
	print('Testing phase: Cross')
	crosses = [0.005, 0.05, 0.10, 0.15, 0.20, 0.30, 0.50]
	for cross in crosses:
		args = {
			'instances': 300,
			'iterations': 500,
			'keepBest': int(0.1 * 300),
			'keepWorst': int(0.07 * 300),
			'cross': int(cross * 300),
			'mutationFactor': 0.001,
			'maxClauses': 40 }
		fname = ""
		for key in ['instances', 'iterations', 'keepBest', 'keepWorst', 'cross', 'mutationFactor']:
			fname += str(args[key]) + "_"
		fname = "data/cross/" + fname.strip() + ".dat"
		with open(fname, 'w') as output:
			for line in run(args):
				output.write(line)

def testMutation():
	print('Testing phase: Mutation')
	mutations = [0.001, 0.005, 0.05, 0.10, 0.15, 0.20, 0.25, 0.50]
	for mutation in mutations:
		args = {
			'instances': 300,
			'iterations': 500,
			'keepBest': int(0.1 * 300),
			'keepWorst': int(0.07 * 300),
			'cross': int(0.07 * 300),
			'mutationFactor': mutation,
			'maxClauses': 40 }
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