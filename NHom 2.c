
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h> 

typedef struct {
    int ngay, thang, nam;
} NgaySinh;

typedef struct {
    char maSV[10];
    char hoTen[50];
    char gioiTinh[5];
    char sdt[12];
    NgaySinh ngaySinh;
} SinhVien;


int nhapThongTin(SinhVien ds[], int n); 
void hienThi(SinhVien sv);
void hienThiDanhSach(SinhVien ds[], int n);
int addStudents(SinhVien ds[], int n);
void updateStudent(SinhVien ds[], int n);
int xoaSinhVien(SinhVien ds[], int n);
void timKiemSinhVien(SinhVien ds[], int n);
void sortStudentsByName(SinhVien ds[], int n);
int findById(SinhVien ds[], int n, char id[]); 
int isValidDate(int ngay, int thang, int nam); 

int main() {
    SinhVien ds[100];
    int n = 0;
    int choose;

    do {
        printf("\n===========================MENU==========================\n");
        printf("||1.Nhap thong tin sinh vien.                            ||\n");
        printf("||2.Hien thi danh sach cua sinh vien.                   ||\n");
        printf("||3.Them moi 1 sinh vien (vao dau mang).                ||\n");
        printf("||4.Cap nhat thong tin sinh vien (ko update id)         ||\n");
        printf("||5.Xoa danh sach sinh vien theo ID                     ||\n");
        printf("||6.Tim kiem thong tin sinh vien theo ten               ||\n");
        printf("||7.Sap xep danh sach sinh vien theo ten tang dan (A-Z).||\n");
        printf("||8.Thoat.                                              ||\n");
        printf("=========================================================\n");
        printf("Hay nhap chuc nang ma ban can: ");
        scanf("%d", &choose);

        switch(choose) {
            case 1: 
                n = nhapThongTin(ds, n); 
                break;
            case 2: 
                hienThiDanhSach(ds, n);
                break; 
            case 3: 
                n = addStudents(ds, n);
                break;
            case 4: 
                updateStudent(ds, n);
                break; 
            case 5: 
                n = xoaSinhVien(ds, n);
                break;
            case 6: 
                timKiemSinhVien(ds, n);
                break; 
            case 7: 
                sortStudentsByName(ds, n);
                break;
            case 8: 
                printf("Cam on ban da su dung chuong trinh.\n"); 
                break; 
            default:
                printf("Loi - xin vui long nhap tu 1 - 8\n"); 
        }
    } while (choose != 8); 
    
    return 0;
}


int nhapThongTin(SinhVien ds[], int n) {
    int soLuong;
    printf("Nhap so luong sinh vien can them: ");
    scanf("%d", &soLuong);
    
    if (n + soLuong > 100) {
        printf("Vuot qua gioi han! Chi co the them %d sinh vien.\n", 100 - n);
        soLuong = 100 - n;
    }
    
    for (int i = 0; i < soLuong; i++) {
        printf("\n=== NHAP THONG TIN SINH VIEN THU %d ===\n", n + i + 1);
        
        SinhVien sv;
        
        printf("Nhap ma sinh vien: ");
        scanf("%s", sv.maSV);
        
       
        int giongMa = 0;
        for (int j = 0; j < n + i; j++) {
            if (strcmp(ds[j].maSV, sv.maSV) == 0) {
                giongMa = 1;
                break;
            }
        }
        if (giongMa) {
            printf("Ma sinh vien da ton tai! Vui long nhap lai.\n");
            i--;
            continue;
        }
        
        printf("Nhap ho ten: ");
        getchar();
        fgets(sv.hoTen, sizeof(sv.hoTen), stdin);
        sv.hoTen[strcspn(sv.hoTen, "\n")] = '\0';
        
        printf("Nhap gioi tinh: ");
        scanf("%4s", sv.gioiTinh);
        
        printf("Nhap so dien thoai: ");
        scanf("%11s", sv.sdt);
        
        printf("Nhap ngay sinh (dd mm yyyy): ");
        scanf("%d %d %d", &sv.ngaySinh.ngay, &sv.ngaySinh.thang, &sv.ngaySinh.nam);
        
        if (!isValidDate(sv.ngaySinh.ngay, sv.ngaySinh.thang, sv.ngaySinh.nam)) {
            printf("Ngay sinh khong hop le! Vui long nhap lai.\n");
            i--;
            continue;
        }
        
        ds[n + i] = sv;
        printf("Da them sinh vien thanh cong!\n");
    }
    
    return n + soLuong;
}


void hienThi(SinhVien sv) {
    printf("%-7s | %-20s | %-4s | %-10s | %02d/%02d/%04d\n",
           sv.maSV, sv.hoTen, sv.gioiTinh, sv.sdt,
           sv.ngaySinh.ngay, sv.ngaySinh.thang, sv.ngaySinh.nam);
}

void hienThiDanhSach(SinhVien ds[], int n) {
    if (n == 0) {
        printf("Danh sach rong!\n");
        return;
    }
    printf("\n=== DANH SACH SINH VIEN ===\n");
    printf("MaSV   | Ho ten              | GT   | SDT        | Ngay sinh\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
        hienThi(ds[i]);
}


int isValidDate(int ngay, int thang, int nam) {
    if (thang < 1 || thang > 12) return 0;
    if (ngay < 1) return 0;
    
    int ngayTrongThang;
    if (thang == 2) {
        ngayTrongThang = ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0)) ? 29 : 28;
    } else if (thang == 4 || thang == 6 || thang == 9 || thang == 11) {
        ngayTrongThang = 30;
    } else {
        ngayTrongThang = 31;
    }
    
    return (ngay <= ngayTrongThang);
}


int addStudents(SinhVien ds[], int n) {
    if (n >= 100) {
        printf("Danh sach da day!\n");
        return n;
    }
    
    SinhVien sv;
    printf("\n=== THEM SINH VIEN VAO DAU MANG ===\n");
    
    printf("Nhap ma sinh vien: ");
    scanf("%9s", sv.maSV);
    
    
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].maSV, sv.maSV) == 0) {
            printf("Ma sinh vien da ton tai!\n");
            return n;
        }
    }
    
    printf("Nhap ho ten: ");
    getchar();
    fgets(sv.hoTen, sizeof(sv.hoTen), stdin);
    sv.hoTen[strcspn(sv.hoTen, "\n")] = '\0';
    
    printf("Nhap gioi tinh: ");
    scanf("%4s", sv.gioiTinh);
    
    printf("Nhap so dien thoai: ");
    scanf("%11s", sv.sdt);
    
    printf("Nhap ngay sinh (dd mm yyyy): ");
    scanf("%d %d %d", &sv.ngaySinh.ngay, &sv.ngaySinh.thang, &sv.ngaySinh.nam);
    
    if (!isValidDate(sv.ngaySinh.ngay, sv.ngaySinh.thang, sv.ngaySinh.nam)) {
        printf("Ngay sinh khong hop le!\n");
        return n;
    }
    
    
    for (int i = n; i > 0; i--) {
        ds[i] = ds[i - 1];
    }
    
    ds[0] = sv;
    printf("Da them sinh vien vao dau mang!\n");
    return n + 1;
}


int findById(SinhVien ds[], int n, char id[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].maSV, id) == 0) {
            return i;
        }
    }
    return -1;
}


void updateStudent(SinhVien ds[], int n) {
    if (n == 0) {
        printf("Danh sach rong!\n");
        return;
    }
    
    char id[10];
    printf("Nhap ma sinh vien can cap nhat: ");
    scanf("%9s", id);
    
    int pos = findById(ds, n, id);
    if (pos == -1) {
        printf("Khong tim thay sinh vien!\n");
        return;
    }
    
    printf("\nThong tin hien tai:\n");
    hienThi(ds[pos]);
    
    printf("\nNhap thong tin moi:\n");
    printf("Nhap ho ten moi: ");
    getchar();
    fgets(ds[pos].hoTen, sizeof(ds[pos].hoTen), stdin);
    ds[pos].hoTen[strcspn(ds[pos].hoTen, "\n")] = '\0';
    
    printf("Nhap gioi tinh moi: ");
    scanf("%4s", ds[pos].gioiTinh);
    
    printf("Nhap so dien thoai moi: ");
    scanf("%11s", ds[pos].sdt);
    
    printf("Nhap ngay sinh moi (dd mm yyyy): ");
    scanf("%d %d %d", &ds[pos].ngaySinh.ngay, &ds[pos].ngaySinh.thang, &ds[pos].ngaySinh.nam);
    
    if (!isValidDate(ds[pos].ngaySinh.ngay, ds[pos].ngaySinh.thang, ds[pos].ngaySinh.nam)) {
        printf("Ngay sinh khong hop le!\n");
        return;
    }
    
    printf("Da cap nhat thong tin thanh cong!\n");
}


int xoaSinhVien(SinhVien ds[], int n) {
    if (n == 0) {
        printf("Danh sach rong!\n");
        return n;
    }
    
    char ma[10];
    printf("Nhap ma SV can xoa: ");
    scanf("%9s", ma);
    
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].maSV, ma) == 0) {
            for (int j = i; j < n - 1; j++) {
                ds[j] = ds[j + 1];
            }
            printf("Da xoa sinh vien thanh cong!\n");
            return n - 1;
        }
    }
    
    printf("Khong tim thay sinh vien!\n");
    return n;
}


void timKiemSinhVien(SinhVien ds[], int n) {
    if (n == 0) {
        printf("Danh sach rong!\n");
        return;
    }
    
    char key[50], nameLower[50], keyLower[50];
    printf("Nhap ten can tim: ");
    getchar();
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    
    strcpy(keyLower, key);
    for (int j = 0; keyLower[j]; j++) {
        keyLower[j] = tolower(keyLower[j]);
    }
    
    int found = 0;
    printf("\n=== KET QUA TIM KIEM ===\n");
    
    for (int i = 0; i < n; i++) {
        strcpy(nameLower, ds[i].hoTen);
        for (int j = 0; nameLower[j]; j++) {
            nameLower[j] = tolower(nameLower[j]);
        }
        
        if (strstr(nameLower, keyLower) != NULL) {
            found = 1;
            hienThi(ds[i]);
        }
    }
    
    if (!found) {
        printf("Khong tim thay sinh vien!\n");
    }
}


void sortStudentsByName(SinhVien ds[], int n) {
    if (n <= 1) {
        printf("Khong du sinh vien de sap xep!\n");
        return;
    }
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(ds[j].hoTen, ds[j + 1].hoTen) > 0) {
                SinhVien temp = ds[j];
                ds[j] = ds[j + 1];
                ds[j + 1] = temp;
            }
        }
    }
    
    printf("Da sap xep danh sach theo ten thanh cong!\n");
}

