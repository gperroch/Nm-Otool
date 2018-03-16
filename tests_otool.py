import sys, os, re

path = sys.argv[1]
currentpath = os.path.dirname(os.path.abspath(__file__))
fd = open(currentpath + "/result_tests_otool", "a")

outp = input("Write the results in files ?(y/n): ")
for dirpath, dirnames, filenames in os.walk(path):
	for filename in filenames:
		cmd_ft_otool = re.escape(currentpath) + "/ft_otool " + re.escape(dirpath) + "/" + re.escape(filename) + " &> " + re.escape(currentpath) + "/result_ft_otool"
		cmd_otool = "otool -t " + re.escape(dirpath) + "/" + re.escape(filename) + " &> " + re.escape(currentpath) + "/result_otool"
		cmd_comparison_otool = "diff " + re.escape(currentpath) + "/result_otool " + re.escape(currentpath) + "/result_ft_otool" + " &> " + re.escape(currentpath) + "/result_diff_otool"

		print("Starting test on: " + re.escape(dirpath) + "/" + re.escape(filename))
		os.system(cmd_ft_otool)
		os.system(cmd_otool)
		os.system(cmd_comparison_otool)

		cmp_file_otool = open(currentpath + "/result_diff_otool", "r")
		otool_file = open(currentpath + "/result_otool", "r")
		ft_otool_file = open(currentpath + "/result_ft_otool", "r")

		cmp_line = cmp_file_otool.readline()
		otool_line = otool_file.readline()
		ft_otool_line = ft_otool_file.readline()
		if len(cmp_line) > 1:
			print("cmp_line: " + cmp_line)
			if otool_line.endswith("is not an object file")\
			and ft_otool_line.endswith("is not an object file"):
				print("File: " + dirpath + "/" + filename + " not recognized by both otool and ft_otool.")
			elif otool_line.endswith("Permission denied\n") and ft_otool_line.endswith("Permission denied.\n"):
				print("File: " + dirpath + "/" + filename + " permission denied on both otool and ft_otool.")
			elif otool_line.endswith("No such file or directory.\n") and ft_otool_line.endswith("No such file or directory.\n"):
				print("File: " + dirpath + "/" + filename + " file not found by both otool and ft_otool.")
			elif outp.startswith("y"):
				fd.write("Different results on: " + dirpath + "/" + filename + " on otool\n")
			else:
				print("Different results on: " + dirpath + "/" + filename + " on otool.")
		elif outp.startswith("n"):
			print("OK: " + dirpath + "/" + filename)

		cmp_file_otool.close()
		otool_file.close()
		ft_otool_file.close()

#		input()

## Boucle qui parcours le result_tests et recupere toutes les extensions des
## fichiers en erreur, ainsi qu'un fichier d'exemple a chaque ('supprime' les
## doublons d'extensions)

#fd.seek(0)
#for line in fd.readline();
