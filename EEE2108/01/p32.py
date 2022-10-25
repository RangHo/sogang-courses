name = input("Enter your birthday in the following form: \nMM/DD/YYYY \n");
FirstSlash = name[2];
SecondSlash = name[5];
if FirstSlash == '/':
    if SecondSlash == '/':
        print("You were born in the year",name[6:10:1],".");
    else:
        print("Please Enter in the Correct Format.");
else:
    print("Please Enter in the Correct Format.");

