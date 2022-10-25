x = int(input("Enter an integer\n"));
anss = 0;
for i in range(2,7):
    #print("i =", i);
    root = 0;
    guess = 0;
    if(x < 0):
        while(guess >= x):
            if(i % 2 == 0):
                #print("i is even and", i);
                break;
            else:
                #print("i is odd and", i);
                guess = root ** i;
                
                if(guess != x):
                    #print("root =",root, "pwr =",i,"guess =", guess);
                    root = root -1;

                elif(guess == x):
                    print("[root =",root, "pwr =",i,"]");
                    anss =  anss + 1;
                    break;
    else:
        while(guess <= x):
            guess = root ** i;
            if(guess != x):
                root = root +1;
                #print("root =",root, "pwr =",i, "guess =",guess);

            elif(guess == x):
                print("[root =",root, "pwr =",i,"]");
                anss =  anss + 1;
                break;
if(anss == 0):
    print("No pairs found.");