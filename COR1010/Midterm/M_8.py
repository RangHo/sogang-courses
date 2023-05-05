source = input("Enter any string to uncompress : ")
result = ""

target_char = ''
target_count = '0'
for c in source:
    if c.isdigit():
        target_count += c
    else:
        result += (target_char * int(target_count))
        target_char = c
        target_count = '0'
else:
    result += (target_char * int(target_count))

print(result)
