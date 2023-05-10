#include<stdio.h>
#include<string.h>
#define MAXLENGTH 50
typedef struct{
    float Toan;
    float Ly;
    float Hoa;
}Monhoc;
typedef struct{
    char Ten[MAXLENGTH];
    char ID[MAXLENGTH];
    float Diemtrungbinh;
    int Tuoi;
}Thongtin;
typedef struct{
    Monhoc Tohopmonhoc;
    Thongtin Thongtin;
}Sinhvien;
typedef struct{
    Sinhvien Danhsachsinhvien[MAXLENGTH];
    int Soluong;
}Lophoc;
void Makenulllist(Lophoc *Class){
    Class->Soluong = 0;
}
int Emptylist(Lophoc Class){
    return Class.Soluong==0;
}
int Fulllist(Lophoc Class){
    return Class.Soluong==MAXLENGTH;
}
int Firstlist(Lophoc Class){
    return 1;
}
int Lastlist(Lophoc Class){
    return Class.Soluong+1;
}
int NextPosition(Lophoc Class, int Position){
    return Position+1;
}
int Prev(Lophoc Class, int Position){
    return Position-1;
}
Sinhvien Retrieve(Lophoc Class, int Position){
    return Class.Danhsachsinhvien[Position-1];
}
float Diemtrungbinh(float T, float L, float H){
    return (T+L+H)/3;
}
Sinhvien Addstudent(){
    Sinhvien Element;
    printf("Nhập vào tên sinh viên:\n");
    gets(Element.Thongtin.Ten);
    printf("Nhập vào id sinh viên:\n");
    gets(Element.Thongtin.ID);
    printf("Nhập vào tuổi sinh viên:\n");
    scanf("%d",&Element.Thongtin.Tuoi);
    printf("Nhập vào điểm toán:\n");
    scanf("%f",&Element.Tohopmonhoc.Toan);
    printf("Nhập vào điểm lý:\n");
    scanf("%f",&Element.Tohopmonhoc.Ly);
    printf("Nhập vào điểm hóa:\n");
    scanf("%f",&Element.Tohopmonhoc.Hoa);
    float T = Element.Tohopmonhoc.Toan;
    float L = Element.Tohopmonhoc.Ly;
    float H = Element.Tohopmonhoc.Hoa;
    Element.Thongtin.Diemtrungbinh = Diemtrungbinh(T,L,H);
    return Element;
}
void Insert(Lophoc *Class, int Position, Sinhvien Element){
    if(Fulllist(*Class)){
        printf("Lớp đã đầy sỉ số!!!\n");
    }else if(Position<Firstlist(*Class)||Position>Lastlist(*Class)){
        printf("Chỗ ngồi không hợp!!!\n");
    }else{
        for(int P = Class->Soluong;P>=Position;P--){
            Class->Danhsachsinhvien[P] = Class->Danhsachsinhvien[P-1];
        }
        Class->Soluong++;
        Class->Danhsachsinhvien[Position-1] = Element;
    }
}
void Delete(Lophoc *Class, int Position){
    if(Emptylist(*Class)){
        printf("Còn ai trong lớp đâu mà xóa.\n");
    }else if(Position<Firstlist(*Class)||Position>Lastlist(*Class)-1){
        printf("Vị trí xóa không tồn tại.\n");
    }else{
        for(int P = Position;P<Lastlist(*Class)-1;P++){
            Class->Danhsachsinhvien[P-1] = Class->Danhsachsinhvien[P];
        }
        Class->Soluong--;
    }
}
void Readlist(Lophoc *Class){
    Makenulllist(Class);
    Sinhvien Element;
    printf("Nhập vào số lượng sinh viên.\n");
    int Soluong;
    scanf("%d",&Soluong);
    for(int i=0;i<Soluong;i++){
        printf("\n");
        getchar();
        Element = Addstudent();
        Insert(Class,Lastlist(*Class),Element);
    }
}
void Printelement(Lophoc Class, int Position){
    Sinhvien Element = Retrieve(Class,Position);
    printf("Thông tin sinh viên thứ %d\n",Position);
    printf("    - Họ và tên: %s\n",Element.Thongtin.Ten);
    printf("    - Mã số sinh viên: %s\n",Element.Thongtin.ID);
    printf("    - Tuổi: %d\n",Element.Thongtin.Tuoi);
    printf("    - Điểm số các môn học:\n");
    printf("        + Toán: %.2f\n",Element.Tohopmonhoc.Toan);
    printf("        + Lý: %.2f\n",Element.Tohopmonhoc.Ly);
    printf("        + Hóa: %.2f\n",Element.Tohopmonhoc.Hoa);
    printf("        + Điểm trung bình: %.2f\n\n",Element.Thongtin.Diemtrungbinh);
}
void Printlist(Lophoc Class){
    int Position = Firstlist(Class);
    while(Position!=Lastlist(Class)){
        Printelement(Class,Position);
        Position = NextPosition(Class,Position);
    }
    printf("\n");
}
void Swap(Sinhvien *A, Sinhvien *B){
    Sinhvien Temp = *A;
    *A = *B;
    *B = Temp;
}
void Xephang(Lophoc *Class){
    int i = Firstlist(*Class);
    while(i!=Lastlist(*Class)-1){
        Sinhvien *EF = &Class->Danhsachsinhvien[i-1];
        int j = NextPosition(*Class,i);
        while(j!=Lastlist(*Class)){
            Sinhvien *EN = &Class->Danhsachsinhvien[j-1];
            if((*EF).Thongtin.Diemtrungbinh<(*EN).Thongtin.Diemtrungbinh){
                Swap(EF,EN);
            }
            j = NextPosition(*Class,j);
        }
        i = NextPosition(*Class,i);
    }
}
void Timsinhvien(Lophoc Class){
    getchar();
    printf("Nhập vào mã số sinh viên cần tìm.\n");
    char ID[MAXLENGTH];
    gets(ID);
    Sinhvien Element;
    int i = Firstlist(Class);
    while(i!=Lastlist(Class)){
        Element = Retrieve(Class,i);
        if(strcmp(ID,Element.Thongtin.ID)==0){
            Printelement(Class,i);
            return;
        }
        i = NextPosition(Class,i);
    }
    printf("Không tìm thấy sinh viên có mã số %s",ID);
}
void Hocluc(Lophoc Class){
    Lophoc Nhom[4];
    for(int i=0;i<4;i++){
        Makenulllist(&Nhom[i]);
    }
    Sinhvien Element;
    float Diem;
    int i = Firstlist(Class);
    while(i!=Lastlist(Class)){
        Element = Retrieve(Class,i);
        Diem = Element.Thongtin.Diemtrungbinh;
        if(Diem>=9){
            Insert(&Nhom[0],Lastlist(Nhom[0]),Element);
        }else if(Diem>=7&&Diem<9){
            Insert(&Nhom[1],Lastlist(Nhom[1]),Element);
        }else if(Diem>=5&&Diem<7){
            Insert(&Nhom[2],Lastlist(Nhom[2]),Element);
        }else{
            Insert(&Nhom[3],Lastlist(Nhom[3]),Element);
        }
        i = NextPosition(Class,i);
    }
    for(int i=0;i<4;i++){
        printf("Danh sách sinh viên loại %d.\n",i+1);
        Printlist(Nhom[i]);
    }
}
void Thaydoi(Lophoc *Class){
    printf("Bạn muốn thêm hay xóa sinh viên.\n");
    Return:
    printf("Nhập (1) nếu thêm, (2) nếu xóa và (-1) để thoát.\n");
    int Selection;
    scanf("%d",&Selection);
    if(Selection==1){
        getchar();
        Sinhvien Element = Addstudent();
        printf("Nhập vào vị trí cần chèn vào.\n");
        int Position;
        scanf("%d",&Position);
        Insert(Class,Position,Element);
        printf("Đã thêm sinh viên vào danh sách.\n");
    }else if(Selection==2){
        printf("Nhập mã số sinh viên cần xóa.\n");
        char ID[MAXLENGTH];
        getchar();
        gets(ID);
        int i = Firstlist(*Class);
        while(i!=Lastlist(*Class)){
            if(strcmp(ID,Retrieve(*Class,i).Thongtin.ID)==0){
                Delete(Class,i);
                printf("Đã xóa sinh viên khỏi danh sách.\n");
                return;
            }
            i = NextPosition(*Class,i);
        }
        printf("Không tìm thấy sinh viên cần xóa.\n");
    }else if(Selection==-1){
        printf("Đã hủy thao tác này.\n");
    }else{
        printf("Bạn nhập sai thao tác, mời nhập lại.\n");
        goto Return;
    }
}
int main(int argc, char const *argv[]){
    Lophoc Class;
    Readlist(&Class);
    printf("\n");
    Printlist(Class);
    Thaydoi(&Class);
    printf("\n");
    Printlist(Class);
}