#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
// Hàm trả về một số nguyên ngẫu nhiên trong khoảng từ Min đến Max
int GetRandom(int Min, int Max) {
    return Min+(int)(rand()*(Max-Min+1.0)/(1.0 + RAND_MAX));
}
// Hàm nhập mảng với số lượng phần tử là Num
void Input(int *&Array, int Num) {
    // Khởi tạo giá trị ngẫu nhiên cho mảng
    srand((unsigned int)time(NULL));
    // Cấp phát bộ nhớ cho mảng
    Array = (int*)malloc(sizeof(int) * Num);
    // Nhập giá trị ngẫu nhiên cho mảng
    for (int i = 0; i < Num; i++) {
        *(Array + i) = GetRandom(0, 1000000);
    }
}
void Input(int **Array, int Num) {
    // Khởi tạo giá trị ngẫu nhiên cho mảng
    srand((unsigned int)time(NULL));
    // Cấp phát bộ nhớ cho mảng
    *Array = (int*)malloc(sizeof(int) * Num);
    // Nhập giá trị ngẫu nhiên cho mảng
    for (int i = 0; i < Num; i++) {
        *(*Array + i) = GetRandom(0, 10000);
    }
}
//Không nên sử dụng con trỏ đơn là tham số đầu vào của một hàm bất kỳ nếu hàm đó có chức năng cấp phát hoặc thay đổi kích thước vùng nhớ,vì khi sử dụng con trỏ đơn, hàm đấy sẽ được nhận vào 1 bản sao của con trỏ mà bạn truyền từ bên ngoài vào, khi hàm đấy cấp phát hoặc thay đổi kích thước vùng nhớ thì chỉ có bản sao bị thay đổi còn bản gốc(ở bên ngoài hàm) không thay đổi,để giải quyết vấn đề này bạn hãy sử dụng con trỏ trỏ đến con trỏ đấy(con trỏ đôi) hoặc tham chiếu đến con trỏ đấy(tham khảo 2 hàm Input() bên trên)

// Hàm xuất mảng với số lượng phần tử là Num
void Output(int *Array, int Num) {
    // Xuất từng phần tử của mảng
    for (int i = 0; i < Num; i++) {
        printf("%d, ", *(Array + i));
    }
}
// Hàm hoán đổi giá trị của hai biến
void Swap(int *Value1, int *Value2) {
    int Temp = *Value1;
    *Value1 = *Value2;
    *Value2 = Temp;
}
// Thuật toán sắp xếp nổi bọt (Bubble Sort)
void Bubble_Sort(int *Array, int Num) {
    for (int i = 0; i < Num - 1; i++) { // Lặp qua từng phần tử của mảng
        for (int j = Num - 1; j > i; j--) { // Lặp qua các phần tử còn lại của mảng
            if (*(Array + j) < *(Array + j - 1)) { // Nếu phần tử sau nhỏ hơn phần tử trước
                Swap(Array + j, Array + j - 1); // Hoán đổi giá trị của 2 phần tử
            }
        }
    }
}
// Thuật toán sắp xếp chọn (Selection Sort)
void Selection_Soft(int *Array, int Num) {
    int Min = 0;
    // Duyệt qua từng phần tử của mảng
    for (int i = 0; i < Num - 1; i++) {
        Min = i;
        // Tìm kiếm phần tử nhỏ nhất trong mảng
        for (int j = i + 1; j < Num; j++) {
            if (*(Array + Min) > *(Array + j)) {
                Min = j;
            }
        }
        // Đổi chỗ phần tử nhỏ nhất với phần tử đầu tiên của mảng chưa được sắp xếp
        if (Min != i) {
            Swap(Array + i, Array + Min);
        }
    }
}
// Thuật toán sắp xếp chèn (Insertion Sort)
void Insertion_Sort(int *Array, int Num) {
    int Pin = 0, Value;
    // Duyệt qua từng phần tử của mảng
    for (int i = 1; i < Num; i++) {
        Value = *(Array + i);
        // Di chuyển các phần tử lớn hơn giá trị hiện tại về phía sau của mảng
        for (Pin = i; (Pin > 0) && (*(Array + Pin - 1) > Value); Pin--) {
            *(Array + Pin) = *(Array + Pin - 1);
        }
        // Chèn giá trị hiện tại vào vị trí đúng trong mảng
        *(Array + Pin) = Value;
    }
}
// Thuật toán sắp xếp đổi chỗ (Interchange Sort)
void Interchange_Sort(int *Array, int Num) {
    // Duyệt qua từng phần tử của mảng
    for (int i = 0; i < Num - 1; i++) {
        // So sánh phần tử hiện tại với các phần tử còn lại của mảng
        for (int j = i + 1; j < Num; j++) {
            if (*(Array + i) > *(Array + j)) {
                // Đổi chỗ phần tử hiện tại với phần tử nhỏ hơn nó
                Swap(Array + i, Array + j);
            }
        }
    }
}
// Thuật toán sắp xếp nhanh (Quick Sort)
void QuickSort1(int *Array, int Left, int Right) {
    // Nếu chỉ có một phần tử hoặc không có phần tử nào, thoát khỏi hàm
    if (Left >= Right) {
        return;
    }
    // Chọn phần tử chốt là phần tử ở giữa của mảng
    int Pivot = *(Array + (Left + Right) / 2);
    int i = Left, j = Right;
    // Sắp xếp các phần tử trong mảng sao cho các phần tử nhỏ hơn phần tử chốt nằm bên trái, các phần tử lớn hơn phần tử chốt nằm bên phải
    do {
        while (*(Array + i) < Pivot) {
            i++;
        }
        while (*(Array + j) > Pivot) {
            j--;
        }
        if (i <= j) {
            // Đổi chỗ phần tử i và phần tử j
            Swap(Array + i, Array + j);
            i++;
            j--;
        }
    } while (i < j);
    // Sắp xếp các phần tử bên trái của phần tử chốt
    QuickSort1(Array, Left, j);
    // Sắp xếp các phần tử bên phải của phần tử chốt
    QuickSort1(Array, i, Right);
}
// Thuật toán sắp xếp trộn (Merge Sort)

// Hàm tìm vị trí của phần tử chốt trong mảng
int FinfPivot(int *Array, int i, int j){
    int FirstKey;
    int k = i+1;
    FirstKey = *(Array+i); // Lấy phần tử đầu tiên làm chốt
    while(k<=j&&*(Array+k)==FirstKey){
        k++; // Tìm phần tử khác chốt để so sánh
    }
    if(k>j){
        return -1; // Nếu không tìm thấy thì trả về -1
    }
    if(*(Array+k)>FirstKey){
        return k; // Nếu phần tử tìm thấy lớn hơn chốt thì trả về vị trí của nó
    }
    return i; // Nếu phần tử tìm thấy nhỏ hơn chốt thì trả về vị trí của chốt
}
// Hàm phân hoạch mảng theo phần tử chốt
int Partition(int *Array, int i, int j, int Pivot){
    int Left,Right;
    Left = i;
    Right = j;
    while(Left<=Right){
        while(*(Array+Left)<Pivot){
            Left++; // Tăng Left cho đến khi gặp phần tử lớn hơn hoặc bằng chốt
        }
        while(*(Array+Right)>=Pivot){
            Right--; // Giảm Right cho đến khi gặp phần tử nhỏ hơn chốt
        }
        if(Left<Right){
            Swap(Array+Left,Array+Right); // Đổi chỗ hai phần tử nếu Left < Right
        }
    }
    return Left; // Trả về vị trí của Left sau khi phân hoạch xong
}
// Hàm sắp xếp nhanh mảng theo thứ tự tăng dần
void QuickSort2(int *Array, int i, int j){
    int Pivot;
    int Pivotindex,k;
    Pivotindex = FinfPivot(Array,i,j); // Tìm vị trí của phần tử chốt
    if(Pivotindex!=-1){
        Pivot = *(Array+Pivotindex); // Lấy giá trị của phần tử chốt
        k = Partition(Array,i,j,Pivot); // Phân hoạch mảng theo phần tử chốt
        QuickSort2(Array,i,k-1); // Sắp xếp nhanh nửa mảng bên trái của phần tử chốt
        QuickSort2(Array,k,j); // Sắp xếp nhanh nửa mảng bên phải của phần tử chốt
    }
}

// Hàm Partition phân hoạch mảng con thành hai mảng con bên trái và bên phải của chốt
int Partition(int *Array, int i, int j){
    int Pivot = Array[i]; // chọn phần tử đầu tiên làm chốt
    int Left = i+1; // chỉ mục cho mảng con bên trái
    int Right = j; // chỉ mục cho mảng con bên phải
    while(Left<=Right){ // vòng lặp while duyệt qua các phần tử của mảng con từ trái sang phải và từ phải sang trái để tìm các phần tử không đúng vị trí so với chốt
        while(Left<=Right&&Array[Left]<=Pivot) Left++; // tìm phần tử bên trái lớn hơn chốt
        while(Left<=Right&&Array[Right]>=Pivot) Right--; // tìm phần tử bên phải nhỏ hơn chốt
        if(Left<Right) Swap(&Array[Left],&Array[Right]); // đổi chỗ hai phần tử nếu chúng không đúng vị trí
    }
    Swap(&Array[Right],&Array[i]); // đưa chốt về vị trí giữa hai mảng con
    return Right; // trả về chỉ mục của chốt
}
// Hàm QuickSort3 sắp xếp một mảng con bằng cách sử dụng thuật toán quick sort
void QuickSort3(int *Array, int i, int j){
    if(i<j){ // nếu mảng con có nhiều hơn một phần tử
        int Par = Partition(Array,i,j); // phân hoạch mảng con bằng hàm Partition
        QuickSort3(Array,i,Par-1); // đệ quy sắp xếp mảng con bên trái của chốt bằng cách gọi lại hàm QuickSort3 với chỉ mục mới là i và Par-1
        QuickSort3(Array,Par+1,j); // đệ quy sắp xếp mảng con bên phải của chốt bằng cách gọi lại hàm QuickSort3 với chỉ mục mới là Par+1 và j
    }
}

// Hàm trộn các phần tử đã sắp xếp trong mảng
void Merge(int *Array, int Left, int Center, int Right) {
    // Tạo mảng tạm để lưu trữ các phần tử đã sắp xếp
    int *Temp = (int*)malloc(sizeof(int) * (Right - Left + 1));
    int Pos = 0;
    int i = Left;
    int j = Center + 1;
    // Sắp xếp các phần tử trong mảng sao cho các phần tử nhỏ hơn nằm bên trái, các phần tử lớn hơn nằm bên phải
    while (!(i > Center && j > Right)) {
        if ((i <= Center && j <= Right && Array[i] < Array[j]) || j > Right) {
            Temp[Pos++] = Array[i++];
        } else {
            Temp[Pos++] = Array[j++];
        }
    }
    // Gán các phần tử đã sắp xếp vào mảng gốc
    for (i = 0; i < Right - Left + 1; i++) {
        Array[Left + i] = Temp[i];
    }
}
void MergeSort1(int *Array, int Left, int Right) {
    // Nếu chỉ có một phần tử hoặc không có phần tử nào, thoát khỏi hàm
    if (Left >= Right) {
        return;
    }
    // Chia mảng thành hai phần bằng nhau
    int Center = (Left + Right) / 2;
    // Sắp xếp các phần tử bên trái của mảng
    MergeSort1(Array, Left, Center);
    // Sắp xếp các phần tử bên phải của mảng
    MergeSort1(Array, Center + 1, Right);
    // Trộn các phần tử đã sắp xếp
    Merge(Array, Left, Center, Right);
}
void Merge(int *Arr, int Left, int Mid, int Right, int *Temp){
    int I = Left; // chỉ mục cho mảng con bên trái
    int J = Mid; // chỉ mục cho mảng con bên phải
    int K = Left; // chỉ mục cho mảng đã trộn
    while(I < Mid && J < Right){ // khi cả hai mảng con có phần tử
        if(Arr[I] < Arr[J]){ // nếu phần tử bên trái nhỏ hơn phần tử bên phải
            Temp[K++] = Arr[I++]; // sao chép phần tử bên trái vào mảng đã trộn và tăng cả hai chỉ mục
        }else{ // nếu không
            Temp[K++] = Arr[J++]; // sao chép phần tử bên phải vào mảng đã trộn và tăng cả hai chỉ mục
        }
    }
    while(I < Mid){ // khi mảng con bên trái còn phần tử
        Temp[K++] = Arr[I++]; // sao chép chúng vào mảng đã trộn và tăng cả hai chỉ mục
    }
    while(J < Right){ // khi mảng con bên phải còn phần tử
        Temp[K++] = Arr[J++]; // sao chép chúng vào mảng đã trộn và tăng cả hai chỉ mục
    }
}
void SplitMerge(int *Temp, int Left, int Right, int *Arr){
    if(Right - Left == 1){ // nếu mảng con chỉ có một phần tử
        return; // trở về không làm gì cả
    }
    int Mid = (Left + Right) / 2; // tìm điểm giữa của mảng con
    SplitMerge(Arr, Left, Mid, Temp); // đệ quy chia và trộn nửa bên trái của mảng con
    SplitMerge(Arr, Mid, Right, Temp); // đệ quy chia và trộn nửa bên phải của mảng con
    Merge(Temp, Left, Mid, Right, Arr); // trộn hai nửa đã sắp xếp của mảng con
}
void MergeSort2(int *Arr,int Num){
    int *Temp = (int*)malloc(sizeof(int) * Num); // cấp phát bộ nhớ cho một mảng tạm thời
    memcpy(Temp,Arr,sizeof(int) * Num); // sao chép mảng ban đầu vào mảng tạm thời
    SplitMerge(Temp,0,Num,Arr); // gọi hàm đệ quy để chia và trộn mảng
    free(Temp); // giải phóng bộ nhớ đã cấp phát
}
// Hàm đẩy phần tử xuống dưới để duy trì tính chất của cây heap
void PushDown(int *Array, int First, int Last){
    int r = First;
    while(r<=(Last-1)/2){
        if(Last==2*r+1){
            if(Array[r]<Array[Last]){
                Swap(&Array[r],&Array[Last]); // Đổi chỗ phần tử cha với phần tử con nếu phần tử cha nhỏ hơn
            }
            r = Last; // Thoát khỏi vòng lặp
        }else if(Array[r]<Array[2*r+1]&&Array[2*r+1]>=Array[2*r+2]){
            Swap(&Array[r],&Array[2*r+1]); // Đổi chỗ phần tử cha với phần tử con trái nếu phần tử cha nhỏ hơn và phần tử con trái lớn hơn hoặc bằng phần tử con phải
            r = 2*r+1; // Tiếp tục đẩy phần tử xuống dưới
        }else if(Array[r]<Array[2*r+2]){
            Swap(&Array[r],&Array[2*r+2]); // Đổi chỗ phần tử cha với phần tử con phải nếu phần tử cha nhỏ hơn
            r = 2*r+2; // Tiếp tục đẩy phần tử xuống dưới
        }else{
            r = Last; // Thoát khỏi vòng lặp
        }
    }
}
// Hàm sắp xếp heap mảng theo thứ tự tăng dần
void HeapSort1(int *Array, int  Num){
    int i;
    for(i=(Num-2)/2;i>=0;i--){
        PushDown(Array,i,Num-1); // Tạo cây heap từ mảng ban đầu
    }
    for(i=Num-1;i>=2;i--){
        Swap(Array+0,Array+i); // Đưa phần tử lớn nhất (gốc của cây heap) về cuối mảng
        PushDown(Array,0,i-1); // Duy trì tính chất của cây heap sau khi đổi chỗ
    }
    Swap(Array+0,Array+1); // Đổi chỗ hai phần tử cuối cùng để hoàn thành sắp xếp
}
// Hàm để duy trì tính chất của min heap cho một nút và các con của nó
void Heapify(int *Array,int n,int i){
    // Tìm chỉ số của nút nhỏ nhất trong ba nút: i (nút cha) và hai con của nó
    int Smallest = i;// Giả sử rằng nút cha là nhỏ nhất
    int Left = 2*i+1;// Chỉ số của con trái
    int Right = 2*i+2;// Chỉ số của con phải
    // So sánh với con trái và cập nhật chỉ số nhỏ nhất nếu cần
    if(Left<n&&*(Array+Left)<*(Array+Smallest)){
        Smallest = Left;
    }
    // So sánh với con phải và cập nhật chỉ số nhỏ nhất nếu cần
    if(Right<n&&*(Array+Right)<*(Array+Smallest)){
        Smallest = Right;
    }
    // Nếu chỉ số nhỏ nhất không phải là i (nút cha), đổi chỗ với nó và gọi hàm heapify cho nút mới đó
    if(Smallest!=i){
        Swap(Array+i,Array+Smallest);
        Heapify(Array,n,Smallest);
    }
}
// Hàm để tạo một min heap từ mảng ban đầu
void BuildHeap(int *Array,int n){
    for(int i =n/2-1;i>=0;i--){
        Heapify(Array,n,i);
    }
}
// Hàm để sắp xếp các phần tử của mảng bằng thuật toán heap sort
void HeapSort2(int *Array,int n){
    BuildHeap(Array,n);
    // Lặp lại cho đến khi kích thước của heap lớn hơn 1:
    for(int i=n-1;i>0;i--){
        // Đổi chỗ phần tử nhỏ nhất (ở gốc của heap) với phần tử cuối cùng của heap
        Swap(Array+0,Array+i);
         // Giảm kích thước của heap đi 1
        n--;
        // Gọi hàm heapify cho gốc của heap để duy trì tính chất của min heap
        Heapify(Array,n,0);
    }
}
void ShellSort(int *Array,int n){
    // Sắp xếp các phần tử ở các khoảng cách n/2, n/4, n/8, ...
    for(int Interval=n/2;Interval>0;Interval/=2){
        // Duyệt qua các phần tử từ vị trí interval đến cuối mảng
        for(int i=Interval;i<n;i++){
            // Lưu giá trị của phần tử hiện tại vào biến temp
            int Temp = *(Array+i);
            int j;
            for(j=i;j>=Interval&&*(Array+(j-Interval))>Temp;j-=Interval){
                *(Array+j) = *(Array+(j-Interval));
            }
            // Gán giá trị của temp vào vị trí thích hợp
            *(Array+j) = Temp;
        }
    }
}
// Thuật toán sắp xếp nhị phân (Binary Sort)
int BinarySearch(int *Array, int Item, int Low, int High) {
    // Nếu chỉ có một phần tử hoặc không có phần tử nào, trả về vị trí chèn của Item
    if (High <= Low) {
        return (Item > *(Array + Low)) ? (Low + 1) : Low;
    }
    int Mid = (Low + High) / 2;
    // Nếu Item đã được tìm thấy, trả về vị trí của Item
    if (Item == *(Array + Mid)) {
        return Mid + 1;
    }
    // Nếu Item lớn hơn phần tử ở giữa, tìm kiếm phần tử bên phải của mảng
    if (Item > *(Array + Mid)) {
        return BinarySearch(Array, Item, Mid + 1, High);
    }
    // Nếu Item nhỏ hơn phần tử ở giữa, tìm kiếm phần tử bên trái của mảng
    return BinarySearch(Array, Item, Low, Mid - 1);
}
void BinSort(int *Array, int n) {
    int i, Loc, j, k, Selected;
    for (i = 1; i < n; ++i) {
        j = i - 1;
        Selected = *(Array + i);
        // Tìm vị trí chèn bằng tìm kiếm nhị phân
        Loc = BinarySearch(Array, Selected, 0, j);
        // Chuyển các phần tử lớn hơn Selected sang phải
        while (j >= Loc) {
            *(Array + (j + 1)) = *(Array + j);
            j--;
        }
        // Chèn Selected vào vị trí đã tìm được
        *(Array + (j + 1)) = Selected;
    }
}
int Max(int Array[], int n) {
  int Max = Array[0];
  for (int i = 1; i < n; i++) {
    if (Array[i] > Max) {
      Max = Array[i];
    }
  }
  return Max;
}
// Hàm sắp xếp Counting Sort
void CountingSort(int *Array, int Num) {
    // Tìm phần tử lớn nhất trong mảng
    int k = Max(Array, Num);
    // Khởi tạo mảng Count với kích thước k + 1 và gán tất cả các phần tử bằng 0
    int Count[k + 1];
    for (int i = 0; i < k + 1; i++) {
        Count[i] = 0;
    }
    // Đếm số lần xuất hiện của mỗi phần tử trong mảng và lưu vào mảng Count
    for (int i = 0; i < Num; i++) {
        Count[Array[i]]++;
    }
    // Tính tích lũy của các giá trị trong mảng Count
    for (int i =1 ;i < k +1 ;i++){
        Count[i]=Count[i]+Count[i-1];
    }
    // Khởi tạo mảng output với kích thước n và gán tất cả các phần tử bằng -1
    int Output[Num];
    for (int i=0;i<Num;i++){
        Output[i]=-1;
    }
    // Duyệt từ cuối đến đầu của mảng đầu vào và đặt các phần tử vào vị trí thích hợp trong mảng Output dựa vào giá trị trong mảng Count
    for (int i=Num-1;i>=0;i--){
        Output[Count[Array[i]]-1]=Array[i];
        Count[Array[i]]--;
    }
    // Sao chép các phần tử từ mảng Output sang lại cho con trỏ Array
    for (int i=0;i<Num;i++){
        *(Array+i)=Output[i];
    }
}
//Hàm đọc 1 dãy số nguyên không xác định số lượng phần tử
void ReadFile(int **Array,int *Num){
    // Mở tệp "Sort.txt" để đọc
    FILE *File = fopen("Sort.txt","r");
    // Nếu không thể mở tệp, hàm trả về ngay lập tức
    if(File==NULL){
        printf("Không tồn tại");
        return;
    }
    // Khởi tạo biến Num bằng 0
    *Num = 0;
    // Khởi tạo dung lượng ban đầu là 10
    int Capacity = 10;
    // Cấp phát bộ nhớ động cho mảng Array với dung lượng ban đầu là Capacity số nguyên
    *Array = (int*)malloc(Capacity*sizeof(int));
    // Nếu cấp phát bộ nhớ thất bại, hàm trả về ngay lập tức
    if(*Array==NULL){
        return;
    }
    // Đọc các số nguyên từ tệp cho đến khi đến cuối tệp
    while(fscanf(File,"%d",*Array+*Num)!=EOF){
        // Tăng biến Num lên 1
        (*Num)++;
        // Kiểm tra xem số lượng số nguyên hiện tại có vượt quá dung lượng của mảng hay không
        if((*Num)>=Capacity){
            // Nếu có, nhân đôi dung lượng và cấp phát lại bộ nhớ cho mảng Array
            Capacity *= 2;
            int *Temp = (int*)realloc(*Array,Capacity*sizeof(int));
            // Nếu cấp phát lại bộ nhớ thất bại, hàm trả về ngay lập tức
            if(Temp==NULL){
                return;
            }
            *Array = Temp;
        }
    }
    // Đóng tệp sau khi đã đọc xong
    fclose(File);
}
void WriteFile(int *Array,int Num){
    FILE *File = fopen("Sort.txt","w");
    for(int i=0;i<Num;i++){
        fprintf(File,"%d ",*(Array+i));
    }
    fclose(File);
}