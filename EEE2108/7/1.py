def merge(left, right): #두개의 Sublist를 Merge 하면서, 크기순으로 정렬하는 단계이다
    result = []         #두 Sublist를 합친 최종 결과가 저장되는 곳이다
    i,j = 0,0           #두 Sublist의 Index이다

    while i < len(left) and j < len(right):
        if left[i] < right[j]:          #왼쪽 Sublist가 작을때
            result.append(left[i])      #숫자가 더 작은 수인, 왼쪽 Sublist의 i번째 수를 Result에 append.
            i += 1                      #왼쪽의 i번째 항목은 처리하였음으로 i++을 한다.

        else:                           #오른쪽Sublist가 작을때
            result.append(right[j])     #숫자가 더 작은 수인, 오른쪽 Sublist의 j번째째 수를 Result에 append
            j += 1                      #오른쪽의 j번째 항목은 처리하였음으로 j++을 한다.

    while (i < len(left)):      #오른쪽 SubList가 비어있을 경우
        result.append(left[i])  #왼쪽의 sublist의 내용을 append
        i += 1

    while (j < len(right)):     #왼쪽의 Sublist가 비어있을 경우
        result.append(right[j]) #오른쪽의 Sublist의 내용을 append
        j += 1
    return result   #합치고 정렬한 결과를 return

def merge_sort(L):  #merge를 이용하여 Merge Sort를 한다.
    if len(L) < 2:  #L 안에 수가 하나 이하로 있는 경우, Sort할 필요가 없기 때문에 바로 출력
        return L[:]
    else:
        middle = len(L)//2              #주어진 L을 반으로 나눈다.
        left = merge_sort(L[:middle])   #왼쪽 Sublist를 다시 Merge Sort
        right = merge_sort(L[middle:])  #오른쪽 Sublist를 다시 Merge Sort
        return merge(left, right)       #앞서 나눈 두 Sublist를 다시 합쳐서 출력.
        
L = [10,9,8,7,6,5,4,3,2,1]
print(merge_sort(L))