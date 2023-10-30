string = input("Enter any string:")
ch = input("Enter any character:")

print("%d is the first index of '%c' in \"%s\"" % (string.index(ch), ch, string))
print("'%c' occurs %d times in \"%s\"" % (ch, string.count(ch), string))
