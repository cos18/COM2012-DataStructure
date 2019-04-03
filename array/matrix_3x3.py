# 2. 두개의 3X3 2차원 배열을 입력 받아서,
#     1) 두 행렬의 합
#     2) 두 행렬의 차
#     3) 두 행렬의 곱
# 연산을 선택하여 출력하는 프로그램을  구현해보세요.

def metrix_sum(m1, m2):
    result = []
    for i in range(9):
        result.append(m1[i]+m2[i])
    return result

def metrix_minus(m1, m2):
    result = []
    for i in range(9):
        result.append(m1[i]-m2[i])
    return result

def metrix_mul(m1, m2):
    result = []
    for i in range(3):
        for j in range(3):
            tmp = m1[3*i] * m2[j]
            tmp += m1[3*i+1] * m2[3+j]
            tmp += m1[3*i+2] * m2[6+j]
            result.append(tmp)
    return result

def print_metrix(m):
    for i in range(3):
        for j in range(3):
            print("{} ".format(m[3*i+j]), end='')
        print()


m1 = []
m2 = []
for i in range(3):
    for j in range(3):
        m1.append(int(input('첫번째 행렬에 넣을 숫자를 입력하세요 : ')))

for i in range(3):
    for j in range(3):
        m2.append(int(input('두번째 행렬에 넣을 숫자를 입력하세요 : ')))

print('첫번째 행렬')
print_metrix(m1)
print()
print('두번째 행렬')
print_metrix(m2)

while True:
    print('실행할 계산을 선택해주세요')
    print('1. 행렬의 덧셈')
    print('2. 행렬의 뺄셈')
    print('3. 행렬의 곱셈')
    print('(나머지 값 입력시 종료)')
    choice = int(input(' >> '))
    if choice == 1:
        print('덧셈 결과')
        print_metrix(metrix_sum(m1, m2))
    elif choice == 2:
        print('뺼셈 결과')
        print_metrix(metrix_minus(m1, m2))
    elif choice == 3:
        print('곱셈 결과')
        print_metrix(metrix_mul(m1, m2))
    else:
        print('종료')
        break
input('')