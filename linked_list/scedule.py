class Scedule:
    def __init__(self, time, desc):
        self.time = time
        self.desc = desc
        self.next = None

def makeScedule(s, time, desc):
    newScedule = Scedule(time, desc);
    if (s[0]==None):
        s[0]=newScedule
        return
    if (s[0].time > time):
        newScedule.next = s[0];
        s[0] = newScedule;
    elif (s[0].time == time):
        print("[ERROR] 같은 시간대에 스케쥴을 두개 이상 만들 수 없습니다.")
        return
    else:
        tmp = s[0]
        while tmp.next:
            if (tmp.next.time == time):
                print("[ERROR] 같은 시간대에 스케쥴을 두개 이상 만들 수 없습니다.")
                return
            if (tmp.next.time > time):
                newScedule.next = tmp.next;
                tmp.next = newScedule;
                break
            tmp = tmp.next
        if(tmp.next == None):
            tmp.next = newScedule

def fixScedule(s, time, change):
    if(s[0]==None or s[0].time > time):
        print("[ERROR] 수정하고 싶은 시간대에 스케쥴이 없습니다.\n")
        return
    if(s[0].time == time):
        s[0].desc = change
        return
    return fixScedule([s[0].next], time, change)

def deleteScedule(s, time):
    if(s[0]==None):
        print("[ERROR] 현재 스케쥴이 비어있습니다.")
        return
    if(s[0].time == time):
        s[0] = s[0].next
        return
    tmp = s[0]
    while(tmp.next):
        if(tmp.next.time > time):
            print("[ERROR] 삭제할 시간대에 스케쥴이 없습니다.")
            return
        if(tmp.next.time==time):
            tmp.next = tmp.next.next
            return
        tmp = tmp.next

def printScedule(s):
    if(s[0] == None):
        return
    print("[{}시 : {}]".format(s[0].time, s[0].desc))
    return printScedule([s[0].next])

saveScedule = [None]
while(True):
    print("\n==스케쥴 관리 프로그램==")
    print("1. 스케쥴 추가")
    print("2. 스케쥴 수정")
    print("3. 스케쥴 삭제")
    print("4. 스케쥴 출력")
    print("(이외 값 입력시 종료)")
    choice = input(" >> ")
    if(choice=="1"):
        time = int(input("스케쥴을 등록할 시간대를 입력하세요.\n >> "))
        desc = input("스케쥴의 상세 내용을 입력해주세요.\n >> ")
        makeScedule(saveScedule, time, desc)
    elif(choice=="2"):
        time = int(input("스케쥴을 수정할 시간대를 입력하세요.\n >> "))
        desc = input("수정할 스케쥴의 상세 내용을 입력해주세요.\n >> ")
        fixScedule(saveScedule, time, desc)
    elif (choice == "3"):
        time = int(input("스케쥴을 삭할 시간대를 입력하세요.\n >> "))
        deleteScedule(saveScedule, time)
    elif (choice == "4"):
        print("===현재 저장되어있는 스케쥴===")
        printScedule(saveScedule)
    else:
        break