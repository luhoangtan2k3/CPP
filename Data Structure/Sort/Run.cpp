#include<stdio.h>
#include<stdlib.h>
#include"Sort.cpp"
int main(int argc, char const *argv[]){
    int Num,*Array,Select;
    Return:
    printf("\nCÁC THAO TÁC NHẬP DỮ LIỆU\n");
    printf("1 - Nhập dữ liệu từ bàn phím\n");
    printf("2 - Nhập dữ liệu từ tệp tin\n");
    printf("0 - Kết thúc chương trình\n");
    printf("\nChọn theo tác nhập dữ liệu\n");
    scanf("%d",&Select);
    switch(Select){
        case 1:
            printf("Số lượng phần tử cần nhập\n");
            scanf("%d",&Num);
            Input(&Array,Num);
            WriteFile(Array,Num);
            printf("Đã thêm %d phần tử\n",Num);
            break;
        case 2:
            ReadFile(&Array,&Num);
            printf("Đã thêm %d phần tử\n",Num);
            break;
        case 0:
            printf("Két thúc chương trình\n");
            return 0;
        default:
            printf("Chỉ 1 trong 2 mục trên\n");
            goto Return;
    }
    printf("\nTỔNG HỢP CÁC THUẬT TOÁN SẮP XẾP:\n");
    printf("1 - Sắp xếp nổi bọt - Bubble Sort\n");
    printf("2 - Sắp xếp chọn - Selection Sort\n");
    printf("3 - Sắp xếp chèn - Insertion Sort\n");
    printf("4 - Đổi chỗ ngay - Interchange Sort\n");
    printf("5 - Sắp xếp nhanh - Quick Sort\n");
    printf("6 - Sắp xếp trộn - Merge Sort\n");
    printf("7 - Sắp xếp vun đống - Heap Sort\n");
    printf("8 - Sắp xếp Shell - Shell Sort\n");
    printf("9 - Sắp xếp thùng - Bin Sort\n");
    printf("10 -Sắp xếp đếm - Counting Sort\n");
    printf("0 - Kết thúc chương trình\n");
    printf("Vui lòng lựa chọn giải thuật\n");
    scanf("%d",&Select);
    switch(Select){
        case 1:
            printf("\nMảng ban đầu:\n");
            Output(Array,Num);
            printf("\nBubble Sort:\n");
            Bubble_Sort(Array,Num);
            Output(Array,Num);
            break;
        case 2:
            printf("\nMảng ban đầu:\n");
            Output(Array,Num);
            printf("\nSelection Sort:\n");
            Selection_Soft(Array,Num);
            Output(Array,Num);
            break;
        case 3:
            printf("\nMảng ban đầu:\n");
            Output(Array,Num);
            printf("\nInsertion Sort:\n");
            Insertion_Sort(Array,Num);
            Output(Array,Num);
            break;
        case 4:
            printf("\nMảng ban đầu:\n");
            Output(Array,Num);
            printf("\nInterchange Sort:\n");
            Interchange_Sort(Array,Num);
            Output(Array,Num);
            break;
        case 5:
            printf("\nMảng ban đầu:\n");
            Output(Array,Num);
            printf("\nQuick Sort:\n");
            //QuickSort1(Array,0,Num-1);
            QuickSort3(Array,0,Num-1);
            //QuickSort2(Array,0,Num-1);
            Output(Array,Num);
            break;
        case 6:
            printf("\nMảng ban đầu:\n");
            Output(Array,Num);
            printf("\nMerge Sort:\n");
            MergeSort2(Array,Num-1);
            //MergeSort1(Array,0,Num-1);
            Output(Array,Num);
            break;
        case 7:
            printf("\nMảng ban đầu:\n");
            Output(Array,Num);
            printf("\nHeap Sort:\n");
            HeapSort1(Array,Num);
            Output(Array,Num);
            break;
        case 8:
            printf("\nMảng ban đầu:\n");
            Output(Array,Num);
            printf("\nShell Sort:\n");
            ShellSort(Array,Num);
            Output(Array,Num);
            break;
        case 9:
            printf("\nMảng ban đầu:\n");
            Output(Array,Num);
            printf("\nBin Sort:\n");
            BinSort(Array,Num);
            Output(Array,Num);
            break;
        case 10:
            printf("\nMảng ban đầu:\n");
            Output(Array,Num);
            printf("\nCounting Sort:\n");
            CountingSort(Array,Num);
            Output(Array,Num);
            break;
        case 0:
            printf("Két thúc chương trình\n");
            break;
    }
    free(Array);
    printf("\n");
    if(Select!=0) goto Return;
}