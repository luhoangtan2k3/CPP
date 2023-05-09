#include<stdio.h>
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
void Printlist(Lophoc Class){
    int Position = Firstlist(Class);
    Sinhvien Element;
    while(Position!=Lastlist(Class)){
        Element = Retrieve(Class,Position);
        printf("Thông tin sinh viên thứ %d\n",Position);
        printf("    - Họ và tên: %s\n",Element.Thongtin.Ten);
        printf("    - Mã số sinh viên: %s\n",Element.Thongtin.ID);
        printf("    - Tuổi: %d\n",Element.Thongtin.Tuoi);
        printf("    - Điểm số các môn học:\n");
        printf("        + Toán: %.2f\n",Element.Tohopmonhoc.Toan);
        printf("        + Lý: %.2f\n",Element.Tohopmonhoc.Ly);
        printf("        + Hóa: %.2f\n",Element.Tohopmonhoc.Hoa);
        printf("        + Điểm trung bình: %.2f\n\n",Element.Thongtin.Diemtrungbinh);
        Position = NextPosition(Class,Position);
    }
    printf("\n");
}
int main(int argc, char const *argv[]){
    Lophoc Class;
    Readlist(&Class);
    printf("\n");
    Printlist(Class);
}