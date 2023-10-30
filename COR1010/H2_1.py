sample = "abcABCdEFaBCDeFAbCdEf"
sample = sample.lower()

index_abc = sample.find("abc")
index_def = sample.rfind("def")
count_abc = sample.count("abc")
count_def = sample.count("def")

print("\"abc 문자열 : %d 인덱스, %d번 존재\"" % (index_abc, count_abc))
print("\"def 문자열 : %d 인덱스, %d번 존재\"" % (index_def, count_def))
