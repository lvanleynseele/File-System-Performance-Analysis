# File-System-Performance-Analysis
In this lab, I investigated the performance of a computer’s file system by comparing the speed of workloads created by different processes.

The goal of this lab was to investigate the performance of a computer’s file system by comparing the speed of workloads created by different processes. By implementing C scripts that read in text in both a sequential and random manner from text files I created, and measuring the time that took, I could see the differences in I/O performance caused by system calls they created. 
	
Both scripts were quite simple. I started with the sequential script, sequential.c, which merely opens the text file passed in from the terminal, stored in argv[1], and reads in each new character in a text file using a while loop and the fread() function. The random script, random.c, was a bit more complicated. It pulls in the input file from the terminal, like sequential.c, checks the length of the file, and then using a for loop over this length, pulls in a random byte, generated with rand(), in this file using the fseek() function. 
	
After implementing the random and sequential scripts, I had to create a set of random files of different sizes to test my scripts. I chose to make text files, 10mB, 25mB, 50mB, 100mB, 200mB, and 500mB in size, containing random ascii characters with the terminal calls:
“[lvanleyn@linux60802 Lab_4]$ base64 /dev/urandom | head -c 10000000 > 10mbfile.txt”
“[lvanleyn@linux60802 Lab_4]$ base64 /dev/urandom | head -c 25000000 > 25mbfile.txt”
“[lvanleyn@linux60802 Lab_4]$ base64 /dev/urandom | head -c 50000000 > 50mbfile.txt”
“[lvanleyn@linux60802 Lab_4]$ base64 /dev/urandom | head -c 100000000 > 100mbfile.txt”
“[lvanleyn@linux60802 Lab_4]$ base64 /dev/urandom | head -c 200000000 > 200mbfile.txt”
“[lvanleyn@linux60802 Lab_4]$ base64 /dev/urandom | head -c 500000000 > 500mbfile.txt”
Once these random text files were created, I then ran each as the input file for both the sequential.c and random.c scripts.
	
To run these input files on my methods, I first compiled each with the terminal calls “[lvanleyn@linux60802 Lab_4]$ gcc -o sequential sequential.c” and “[lvanleyn@linux60802 Lab_4]$ gcc -o random random.c”. I then ran each text file with “[lvanleyn@linux60802 Lab_4]$ time ./sequential 10file.txt” and “[lvanleyn@linux60802 Lab_4]$ time ./random 10file.txt”, changing each time the file name for the subsequent larger file. The time call tracked how long it took each terminal call to run, which allowed me to track the I/O performance of each method. The results are as follows.
	 
	sequential.c time 			random.c time		
file size (mB)	real (Sec)	user (Sec)	sys (Sec)	real (Sec)	user (Sec)	sys (Sec)
10	0.258	0.249	0.009	11.658	1.801	9.857
25	0.531	0.521	0.009	34.182	4.302	29.881
50	0.974	0.957	0.013	73.219	8.74	64.477
100	1.822	1.798	0.023	151.213	17.164	134.051
200	3.534	3.495	0.039	312.014	34.787	277.233
500	8.504	8.41	0.093	800.978	86.345	714.649
	
  Not surprisingly, the sequential script was much faster. This makes sense, because random search could have to span up to the length of the text file to find the next byte, whereas sequential simply has to go to the adjacent byte. Both methods’ overhead grew at close to a linear rate with respect to the file size. It is clear though that random created more of a workload for the system, as, unlike sequential, the sys time was always greater than the user as reported from the time terminal call.

