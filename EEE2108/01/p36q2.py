counter = 0;
lastnum = 0;
currentnum = 0;

while (counter < 10):
    print("Enter an integer to compare. [", 10 - counter, "] numbers remain.")
    currentnum = int(input())
    if(currentnum % 2 == 1):
        if(currentnum > lastnum):
            lastnum = currentnum;
    counter = counter+1;
if(lastnum == 0):
    print("No Odd Numbers were Entered.");
else:
    print("Largest Odd Number is", lastnum);