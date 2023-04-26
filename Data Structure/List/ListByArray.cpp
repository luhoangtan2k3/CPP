#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define MaxLength 100
typedef int Integer;
typedef char String;
typedef float Scores;
struct Student{
    String Name[50];
    String ID[10];
    String Class[10];
    String Sex[3];
    Integer Days,Months,Years,Age;
    Scores DTB;
};
Integer ReturnDays(int Month,int Year){
    switch(Month){
        case 1:case 3:case 5:case 7:case 8:case 10:case 12:
            return 31;
        case 4:case 6:case 9:case 11:
            return 30;
        case 2:
            if((Year%4==0&&Year%100!=0)||Year%400==0){
                return 29;
            }else{
                return 28;
            }
    }
    return 0;
}
//Sử dụng hàm này nếu muốn xóa Enter khi dùng fgets
void Delete_Enter(String String[]){
    size_t Length=strlen(String);
    if(String[Length-1]=='\n'){
        String[Length-1]='\0';
    }
}
void Caps_Lock(String String[]){
    size_t Length=strlen(String);
    for(int i=0;i<Length;i++){
        if(i==0||String[i-1]==32){
            if(String[i]>=97&&String[i]<=122){
                String[i]=String[i]-32;
            }
        }else if(String[i]>=65&&String[i]<=90){
                String[i]=String[i]+32;
        }
    }
}
void Input(Student &Name){
        printf("Nhập vào họ tên sinh viên:\n");
        gets(Name.Name);
        Caps_Lock(Name.Name);
        printf("Nhập vào giới tính sinh viên:\n");
        gets(Name.Sex);
        Return:
            printf("Nhập vào năm sinh của sinh viên:\n");
            scanf("%d %d %d",&Name.Days,&Name.Months,&Name.Years);
        if(Name.Days<1||Name.Days>31||Name.Months<1||Name.Months>12||Name.Years<1)
            goto Return;
        else {
            if(ReturnDays(Name.Months,Name.Years)==30&&Name.Days>30) goto Return;
            else
            if(ReturnDays(Name.Months,Name.Years)==29&&Name.Days>29) goto Return;
            else
            if(ReturnDays(Name.Months,Name.Years)==28&&Name.Days>28) goto Return;
        }
        getchar();
        printf("Nhập vào mã số sinh viên:\n");
        gets(Name.ID);
        printf("Nhập vào mã lớp sinh viên:\n");
        gets(Name.Class);
        do{
            printf("Nhập vào điểm của bạn:\n");
            scanf("%f",&Name.DTB);
        }while(Name.DTB<0||Name.DTB>10);
        getchar();
        printf("\n\n");
}
void Inputs(Student Name[],int &Amount){
    for(int i=0;i<Amount;i++){
        Input(Name[i]);
    }
}
void Output(Student Name){
    printf("Tên: %-25s | Giới tính: %-5s | Tuổi: %-5d | ID: %-10s | Lớp: %-10s | Điểm: %-5.1f \n",Name.Name,Name.Sex,Name.Age,Name.ID,Name.Class,Name.DTB);
}
void Outputs(Student Name[],int Amount){
    for(int i=0;i<Amount;i++){
        Output(Name[i]);
    }
}
void StudentAge(Student Name[],int Amount){
    for(int i=0;i<Amount;i++){
        time_t TIME=time(0);
        tm* Now = localtime(&TIME);
        int YearNow=Now->tm_year+1900;
        Name[i].Age=YearNow-Name[i].Years;
    }
}
void ScoresMax(Student Name[],int Amount){
    printf("Sinh viên có điểm trung bình cao nhất:\n");
    Scores max=Name[0].DTB;
    int Pin=0;
    for(int i=0;i<Amount;i++){
        if(Name[i].DTB>max){
            max=Name[i].DTB;
            Pin=i;
        }
    }
    Output(Name[Pin]);
}
void Swap(Student &Name1,Student &Name2){
    Student Temp = Name1;
    Name1 = Name2;
    Name2 = Temp;
}
void Descending(Student Name[],int Amount){
    printf("Danh sách sinh viên giảm dần:\n");
    for(int i=0;i<Amount-1;i++){
        for(int j=i+1;j<Amount;j++){
            if(Name[i].DTB<Name[j].DTB){
                Swap(Name[i],Name[j]);
            }
        }
    }
    Outputs(Name,Amount);
}
void Ascending(Student Name[],int Amount){
    printf("Danh sách sinh viên tăng dần:\n");
    for(int i=0;i<Amount-1;i++){
        for(int j=i+1;j<Amount;j++){
            if(Name[i].DTB>Name[j].DTB){
                Swap(Name[i],Name[j]);
            }
        }
    }
    Outputs(Name,Amount);
}
void AgeSearch(Student Name[],int Amount){
    int Age,m=0;
    printf("Nhập vào tuổi sinh viên:\n");
    scanf("%d",&Age);
    printf("Danh sách tuổi sinh viên:\n");
    for(int i=0;i<Amount;i++){
        if(Name[i].Age==Age){
            Output(Name[i]);
        }
    }
}
void SearchName(Student Name[],int Amount){
    String N[50];
    printf("Nhập vào Name sinh viên cần tìm :\n");
    gets(N);
    printf("Danh sách Name sinh viên cần tìm:\n");
    for(int i=0;i<Amount;i++){
        if(strstr(Name[i].Name,N)){
            Output(Name[i]);
        }
    }
}
void ClassSearch(Student Name[],int Amount){
    printf("Nhập vào mã lớp sinh viên cần tìm:\n");
    String Class[50];
    gets(Class);
    printf("Danh sách sinh viên theo lớp:\n");
    for(int i=0;i<Amount;i++){
        if(strcmp(Name[i].Class,Class)==0){
            Output(Name[i]);
        }
    }
}
void RemoveStudent(Student Name[],int &Amount){
    printf("Nhập vào ID của sinh viên :\n");
    String MSSV[50];
    gets(MSSV);
    printf("Danh sách sinh viên sau khi xóa:\n");
    for(int i=0;i<Amount;i++){
        if(strcmp(Name[i].ID,MSSV)==0){
            for(int j=i;j<Amount;j++){
                Name[j]=Name[j+1];
            }
            Amount=Amount-1;
        }
    }
    Outputs(Name,Amount);
}
void AddStudent(Student Name[],int &Amount){
    printf("Nhập vào thông tin sinh viên:\n");
    Student NewStudent;
    Input(NewStudent);
    int Location;
    printf("Nhập vào vị trí cần thêm vào:\n");
    scanf("%d",&Location);
    for(int i=Amount;i>=Location;i--){
        Name[i]=Name[i-1];
    }
    Name[Location]=NewStudent;
    Amount++;
    StudentAge(Name,Amount);
    Outputs(Name,Amount);
}
void WriteInFile(Student Name[],int &Amount){
    FILE *File;
    File=fopen("File.bin","wb");
    if(File==NULL){
        printf("Error\n");
    }
    fwrite(&Amount,sizeof(Amount),1,File);
    for(int i=0;i<Amount;i++){
        fwrite(&Name[i],sizeof(Student),1,File);
    }
    fclose(File);
}
void ReadInFile(Student Name[],int Amount){
    FILE *File;
    File=fopen("File.bin","rb");
    if(File==NULL){
        printf("Error\n");
    }
    fread(&Amount,sizeof(Amount),1,File);
    for(int i=0;i<Amount;i++){
        fread(&Name[i],sizeof(Student),1,File);
    }
    Outputs(Name,Amount);
    fclose(File);
}
int main(){
    Student Name[MaxLength];
    Integer Amount,Options;
    do{
        printf("1-Nhập vào danh sách sinh viên:\n");
        printf("2-Xuất danh sách sinh viên:\n");
        printf("3-Sinh viên có điểm trung bình cao nhất:\n");
        printf("4-Tìm kiếm sinh viên theo độ tuổi:\n");
        printf("5-Danh sách sinh viên giảm dần theo ĐTB:\n");
        printf("6-Danh sách sinh viên tăng dần theo ĐTB:\n");
        printf("7-Tìm kiếm sinh viên theo mã lớp:\n");
        printf("8-Tìm kiếm sinh viên theo Name:\n");
        printf("9-Xóa sinh viên bằng ID:\n");
        printf("10-Thêm sinh viên vào vị trí n:\n");
        printf("11-Viết danh sách sinh viên vào file:\n");
        printf("12-Đọc danh sách sinh viên vào file:\n");
        printf("0-Thoát:\n");
        printf("Nhập thao tác của bạn muốn thực hiện:");
        scanf("%d",&Options);
        printf("\n");
        getchar();
        switch(Options){
            case 1:
                printf("Nhập vào số lượng sinh viên:\n");
                scanf("%d",&Amount);
                getchar();
                Inputs(Name,Amount);
                StudentAge(Name,Amount);
                break;
            case 2:
                Outputs(Name,Amount);
                break;
            case 3:
                ScoresMax(Name,Amount);
                break;
            case 4:
                AgeSearch(Name,Amount);
                break;
            case 5:
                Descending(Name,Amount);
                break;
            case 6:
                Ascending(Name, Amount);
                break;
            case 7:
                ClassSearch(Name,Amount);
                break;
            case 8:
                SearchName(Name,Amount);
                break;
            case 9:
                RemoveStudent(Name,Amount);
                break;
            case 10:
                AddStudent(Name,Amount);
                break;
            case 11:
                WriteInFile(Name,Amount);
                break;
            case 12:
                ReadInFile(Name,Amount);
                break;
        }
        printf("\n\n");
    }while(Options!=0);
}