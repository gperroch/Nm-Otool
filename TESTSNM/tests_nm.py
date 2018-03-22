import sys, os, re

path = sys.argv[1]
currentpath = os.path.dirname(os.path.abspath(__file__))
fd = open(currentpath + "/result_tests", "a")

outp = input("Write the results in files ?(y/n): ")
for dirpath, dirnames, filenames in os.walk(path):
	for filename in filenames:
		cmd_ft_nm = re.escape(currentpath) + "/ft_nm " + re.escape(dirpath) + "/" + re.escape(filename) + " &> " + re.escape(currentpath) + "/result_ft_nm"
		cmd_nm = "nm " + re.escape(dirpath) + "/" + re.escape(filename) + " &> " + re.escape(currentpath) + "/result_nm"
		cmd_comparison_nm = "diff " + re.escape(currentpath) + "/result_nm " + re.escape(currentpath) + "/result_ft_nm" + " &> " + re.escape(currentpath) + "/result_diff_nm"

	#	print("Starting test on: " + re.escape(dirpath) + "/" + re.escape(filename))
		os.system(cmd_ft_nm)
		os.system(cmd_nm)
		os.system(cmd_comparison_nm)

		cmp_file_nm = open(currentpath + "/result_diff_nm", "r")
		nm_file = open(currentpath + "/result_nm", "r")
		ft_nm_file = open(currentpath + "/result_ft_nm", "r")

		cmp_line = cmp_file_nm.readline()
		nm_line = nm_file.readline()
		ft_nm_line = ft_nm_file.readline()
		if len(cmp_line) > 1:
			if nm_line.endswith("The file was not recognized as a valid object file\n")\
			and ft_nm_line.endswith("The file was not recognized as a valid object file\n"):
				print("File: " + dirpath + "/" + filename + " not recognized by both nm and ft_nm.")
			elif nm_line.endswith("Permission denied.\n") and ft_nm_line.endswith("Permission denied.\n"):
				print("File: " + dirpath + "/" + filename + " permission denied on both nm and ft_nm.")
			elif nm_line.endswith("No such file or directory.\n") and ft_nm_line.endswith("No such file or directory.\n"):
				print("File: " + dirpath + "/" + filename + " file not found by both nm and ft_nm.")
			elif outp.startswith("y"):
				fd.write("Different results on: " + dirpath + "/" + filename + " on nm\n")
			else:
				print("Different results on: " + dirpath + "/" + filename + " on nm.")
		elif outp.startswith("n"):
			print("OK: " + dirpath + "/" + filename)

		cmp_file_nm.close()
		nm_file.close()
		ft_nm_file.close()

#		input()

## Boucle qui parcours le result_tests et recupere toutes les extensions des
## fichiers en erreur, ainsi qu'un fichier d'exemple a chaque ('supprime' les
## doublons d'extensions)

#fd.seek(0)
#for line in fd.readline();
