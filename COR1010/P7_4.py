num_strs = input("세 개의 정수를 입력하시오 : ").split()

num_ints = []
num_ints.append(int(num_strs[0]))
num_ints.append(int(num_strs[1]))
num_ints.append(int(num_strs[2]))

num_ints.sort()

print("오름차순 : {}".format(num_ints))
