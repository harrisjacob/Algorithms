#!/usr/bin/env python3

import random

studentPool = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
teacherPool = [10, 11, 12, 13, 14, 15, 16, 17, 18, 19]

StudentNames = ["Charles", "Jack", "Megan", "Julie", "Mark", "Emily", "Grace", "Ben", "Noah", "Jared"]
TeacherNames = ["John", "Tim", "Sarah", "Robert", "Max", "Carrie", "Jessica", "Gene", "Ray", "Susan"]

f1 = open("studentData.txt", "w")

for i in range(len(StudentNames)):
	random.shuffle(teacherPool)
	#print("{} {}".format(StudentNames[i], i), end="")
	f1.write("{} {}".format(StudentNames[i], i))
	for j in range(len(teacherPool)):
		#print(" {}".format(teacherPool[j]),end="")
		f1.write(" {}".format(teacherPool[j]))
	#print()
	f1.write("\n")

f1.close()
print("Updated studentData.txt")

f2 = open("teacherData.txt", "w")

for b in range(len(TeacherNames)):
	random.shuffle(studentPool)
	#print("{} {}".format(TeacherNames[b], b), end="")
	f2.write("{} {}".format(TeacherNames[b], b))
	for c in range(len(studentPool)):
		#print(" {}".format(studentPool[c]),end="")
		f2.write(" {}".format(studentPool[c]))
	#print()
	f2.write("\n")

f2.close()
print("Updated teacherData.txt")