# 1. 두 개의 배열을 입력 받아서,
#     1) 각 배열의 값을 정렬
#     2) 두개의 배열을 병합
#     3) 하나의 배열을 작성
# 하는 프로그램을 작성해 보세요.
# 배열에 저장되는 값은 정수입니다

l1 = []
l2 = []
tmp = input('첫번째 배열에 넣을 값을 입력해주세요. (q 입력시 다음 배열로 넘어감) ')
while tmp != 'q':
    tmp = int(tmp)
    l1.append(tmp)
    tmp = input('첫번째 배열에 넣을 값을 입력해주세요. (q 입력시 다음 배열로 넘어감) ')
tmp = input('두번째 배열에 넣을 값을 입력해주세요. (q 입력시 최종 결과로 넘어감) ')
while tmp != 'q':
    tmp = int(tmp)
    l2.append(tmp)
    tmp = input('두번째 배열에 넣을 값을 입력해주세요. (q 입력시 최종 결과로 넘어감) ')
l1.sort()
l2.sort()
p1 = 0
p2 = 0
fl = []
while p1 != len(l1) and p2 != len(l2):
    if l1[p1] > l2[p2]:
        fl.append(l2[p2])
        p2 += 1
    else:
        fl.append(l1[p1])
        p1 += 1
if p1 == len(l1):
    fl += l2[p2:]
else:
    fl += l1[p1:]

print('최종 정렬배열')
print(fl)
input('')