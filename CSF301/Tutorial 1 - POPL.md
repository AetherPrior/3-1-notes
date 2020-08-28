---
title: Tutorial 1 - POPL
created: '2020-08-24T02:44:55.257Z'
modified: '2020-08-24T06:21:24.348Z'
---

# Tutorial 1 - POPL

## Why are not all languages popular?

- takes time to learn a new language, and not entertained for no real use
- People are comfortable with older languages -- developer support for some languages might be less
- Developers go into problem-solving after learning

## Exercise

### 1. WAP to switch every alternating 1 to 0,

```
int flag = 1;
for(char &i: str){
    if(i == '1'){
        if(flag == 1){
            flag = 0; i = '0';
        }
        else if(flag == 0){
            flag =  1;
        }
    }
}
```

### 2. WAP struct and shit

#### C solution

```
typedef struct{
    int ID;
    char name[20];
    float marks;
} student;
int main(void){
    student s1[5];
    for(int i = 0; i <5; i++){
        scanf("%d %s %f", &s1[i].ID, s1[i].name, s1[i].marks);
    }
}
```

#### Java Solution

```
import java.util.Scanner;
class Student{
    int ID;
    String name;
    float marks;
    public Student(int id, String n, float m){
        ID = id;
        name = n;
        marks = m;
    }
}
public class A{
    public static void main(String[] Args){
        Student[] s1 = new Student[5];
        for(int i = 0; i < 5; i++)
        {
            Scanner s = new Scanner(System.in);
            int id = s.nextInt();
            String n = s.next();
            float m = s.nextFloat();
            s1[i] = new Student(id, n, m);
        }
    }
}
```
