cricket = [] 
badminton = [] 
football = [] 

def takeinput(): 
    # Input for cricket players
    cric_nos = int(input("Enter number of students who play cricket: ")) 
    print("Enter roll numbers of students who play cricket:")
    for _ in range(cric_nos): 
        roll_no = int(input()) 
        cricket.append(roll_no) 
    print("Cricket players:", cricket)
    
    # Input for badminton players
    badm_nos = int(input("Enter number of students who play badminton: ")) 
    print("Enter roll numbers of students who play badminton:")
    for _ in range(badm_nos): 
        roll_no = int(input()) 
        badminton.append(roll_no) 
    print("Badminton players:", badminton)
    
    # Input for football players
    foot_nos = int(input("Enter number of students who play football: ")) 
    print("Enter roll numbers of students who play football:")
    for _ in range(foot_nos): 
        roll_no = int(input()) 
        football.append(roll_no) 
    print("Football players:", football)

def result(): 
    # a) Students who play both cricket and badminton
    condition1 = [i for i in cricket if i in badminton] 
    print("List of students who play both cricket and badminton:", condition1)
    
    # b) Students who play either cricket or badminton but not both
    condition2 = [i for i in cricket if i not in badminton] + [j for j in badminton if j not in cricket] 
    print("List of students who play either cricket or badminton but not both:", condition2)
    
    # c) Number of students who play neither cricket nor badminton
    condition3 = [i for i in football if i not in cricket and i not in badminton] 
    print("Number of students who play neither cricket nor badminton:", len(condition3))
    
    # d) Number of students who play cricket and football but not badminton
    condition4 = [i for i in cricket if i in football and i not in badminton] 
    print("Number of students who play cricket and football but not badminton:", len(condition4))

# Call the functions to input data and display results
takeinput() 
result()
