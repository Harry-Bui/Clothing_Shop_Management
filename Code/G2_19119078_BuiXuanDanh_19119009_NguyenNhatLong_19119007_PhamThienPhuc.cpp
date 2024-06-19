#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std; 

struct Sanpham{
    string MSSP;
    string Loai;
    string Ten;
    int Soluong;
    string Ngaynhap;
    int Gia;
};

struct TreeNode { 
    Sanpham data; 
    TreeNode* left= NULL;
    TreeNode* right= NULL; 
};

TreeNode* newNode(Sanpham x){
    TreeNode* q = new TreeNode(); 
    q->data=x;q->left=q->right=NULL;
    return q;
};

TreeNode* add(TreeNode *&p, Sanpham x){
    TreeNode *q = newNode(x); 
    if (p == NULL){
        p = q;
    } else if ((p->data.MSSP == x.MSSP) && (x.MSSP != "")){ 
        p->data.Soluong = p->data.Soluong + x.Soluong;
        p->data.Ngaynhap = x.Ngaynhap;  
    } else if ((x.MSSP[0] <= p->data.MSSP[0]) && (x.MSSP != "")){
        return add(p->left, x); 
    } else if ((x.MSSP[0] > p->data.MSSP[0]) && (x.MSSP != "")){
        return add(p->right, x);
    }
    return p;
}

TreeNode* addNum(TreeNode *&p, Sanpham x){
    TreeNode *q = newNode(x);
    if (p == NULL){
        p = q;
    } else if ((p->data.MSSP == x.MSSP) && (x.MSSP != "")){
        p->data.Soluong = p->data.Soluong + x.Soluong;
    } else if ((x.Soluong < p->data.Soluong) && (x.MSSP != "")){
        return addNum(p->left, x); 
    } else if ((x.Soluong >= p->data.Soluong) && (x.MSSP != "")){
        return addNum(p->right, x);
    }
    return p;
}


TreeNode* MaxofRight(TreeNode *p){
    if (p->right == NULL){
        return p; 
    } else {
        p = MaxofRight(p->right); 
    }
}

void Doc_file_Thong_tin_san_pham_txt(ifstream &filein, Sanpham &data){
    getline(filein, data.MSSP, ',');
    filein.ignore();
    getline(filein, data.Loai, ',');
    filein.ignore();
    getline(filein, data.Ten, ',');
    filein.ignore();
    filein >> data.Soluong;
    filein.ignore();
    filein.ignore(); 
    getline(filein, data.Ngaynhap, ',');
    filein.ignore();
    filein >> data.Gia;
    filein.ignore();
}


void Doc_file(ifstream &filein, Sanpham &sp, TreeNode *&T){
    while(!filein.eof()){
        Doc_file_Thong_tin_san_pham_txt(filein, sp);
        add(T,sp);
    }
}

void Xuatthongtin(Sanpham data){
    if (data.MSSP != ""){
        cout <<"|  "<<setw(9)<<left<<data.MSSP<<"|";
        cout <<"   "<<setw(8)<<left<< data.Loai<<"|";
        cout <<"        "<<setw(19)<<left<<data.Ten<<"|";  
        cout <<"        "<<setw(9)<<left<< data.Soluong<<"|";
        cout <<"     "<<setw(13)<<left<< data.Ngaynhap<<"|";  
        cout <<"  "<<setw(8)<<left<< data.Gia<<"|"<<endl;
    }
}

void Nhapthongtin(Sanpham &data){
    cout <<"\n Vui long nhap thong tin cua san pham:"<<endl;
    cout <<"\t Nhap ID san pham: ";
    getline(cin, data.MSSP);
    cout <<"\n\t Nhap loai san pham: ";
    getline(cin, data.Loai);
    cout <<"\n\t Nhap ten san pham: ";
    getline(cin, data.Ten);
    cout <<"\n\t Nhap so luong san pham: ";
    cin >> data.Soluong;
    cin.ignore();
    cout <<"\n\t Nhap ngay nhap san pham: ";
    getline(cin, data.Ngaynhap);
    cout <<"\n\t Nhap gia cua san pham: ";
    cin >> data.Gia;
    cin.ignore();
}

void Danhsachsanpham(TreeNode *p){
    if (p != NULL){ 
        TreeNode *q = p->right;
        Danhsachsanpham(q);
        Xuatthongtin(p->data);
        q = p->left;
        Danhsachsanpham(q);
    }
}


void TimkiemMSSP(TreeNode *p, string x){
    if (p != NULL){ 
        TreeNode *q = p->right;
        TimkiemMSSP(q, x);
        if (p->data.MSSP == x){
            Xuatthongtin(p->data);
        }
        q = p->left;
        TimkiemMSSP(q, x);
    }
}

void TimkiemLoai(TreeNode *p, string x){
    if (p != NULL){ 
        TreeNode *q = p->right;
        TimkiemLoai(q, x);
        if (p->data.Loai == x){
            Xuatthongtin(p->data);
        }
        q = p->left;
        TimkiemLoai(q, x);
    }
}

void TimkiemTen(TreeNode *p, string x){
    if (p != NULL){ 
        TreeNode *q = p->right;
        TimkiemTen(q, x);
        if (p->data.Ten == x){
            Xuatthongtin(p->data);
        }
        q = p->left;
        TimkiemTen(q, x);
    }
}

void TimkiemSoluong(TreeNode *p, int x){
    if (p != NULL){ 
        TreeNode *q = p->right;
        TimkiemSoluong(q, x);
        if (p->data.Soluong == x){
            Xuatthongtin(p->data);
        }
        q = p->left;
        TimkiemSoluong(q, x);
    }  
}

void TimkiemGia(TreeNode *p, int x){
    if (p != NULL){ 
        TreeNode *q = p->right;
        TimkiemGia(q, x);
        if (p->data.Gia <= x){
            Xuatthongtin(p->data);
        }
        q = p->left;
        TimkiemGia(q, x);
    }
}



void Xuatfile_TXT(TreeNode *p, ofstream &fileout){
    if (p != NULL){
        TreeNode *q = p->right;
        Xuatfile_TXT(q, fileout);
        fileout <<"|  "<<setw(9)<<left<<p->data.MSSP<<"|";
        fileout <<"   "<<setw(8)<<left<< p->data.Loai<<"|";
        fileout <<"        "<<setw(19)<<left<<p->data.Ten<<"|";  
        fileout <<"        "<<setw(9)<<left<< p->data.Soluong<<"|";
        fileout <<"     "<<setw(13)<<left<< p->data.Ngaynhap<<"|";
        fileout <<"  "<<setw(8)<<left<< p->data.Gia<<"|"<<endl;
        q = p->left;
        Xuatfile_TXT(q,fileout);
    }
} 

TreeNode* Timkiem(TreeNode *p, string x){ 

    TreeNode *T = NULL;
    TreeNode *q;
    if (p->data.MSSP == x){
        T = p;
        return T;
    }
    q = p->left;
    T = NULL;
    while (q != NULL && T == NULL){
        T = Timkiem(q, x);
        q = q->right;
    }
    q = p->right;
    while(q != NULL && T == NULL){
        T = Timkiem(q, x);
        q = q->left;
    } 
    return T; 
}

int main(){
    TreeNode *T = NULL;  
    TreeNode *Quanly = NULL; 
    Sanpham phantu;
    string find, MSSP, str, nhanvien;
    int timkiem, yeucau, gia, luachon, soluong;
    int i = 0;
    int tongdoanhthu = 0; 
    ifstream filein;
    ofstream fileout, file; 
    fileout.open("DANHSACH.TXT", ios_base::out);
    while (true){
        system("cls");
        cout <<" =========================================================================================================="<<endl;
        cout <<"|                        TRUONG DAI HOC SU PHAM KY THUAT THANH PHO HO CHI MINH                             |"<<endl;
        cout <<"|                                    Khoa: Dao tao chat luong cao                                          |"<<endl;
        cout <<"|                                                                                                          |"<<endl;
        cout <<"|                                      DE TAI TIEU LUAN CUOI KY                                            |"<<endl;
        cout <<"|                                                                                                          |"<<endl;
        cout <<"|                               MON HOC: GIAI THUAT VA CAU TRUC DU LIEU                                    |"<<endl;
        cout <<"|                       De tai: Thiet ke cau truc du lieu va thuat toan xay dung                           |"<<endl;
        cout <<"|                               chuong trinh quan ly cua hang quan ao                                      |"<<endl;
        cout <<"|==========================================================================================================|"<<endl;
        cout <<"|                                                                                                          |"<<endl;
        cout <<"|                                                                                                          |"<<endl;
        cout <<"|                                   Danh sach sinh vien thuc hien                                          |"<<endl;
        cout <<"|        ============================================================================================      |"<<endl;
        cout <<"|       |      MSSV              |            Ho va ten              |        Muc do dong gop (%)    |     |"<<endl;
        cout <<"|       |------------------------|-----------------------------------|-------------------------------|     |"<<endl;
        cout <<"|       |    19119078            |         Bui Xuan Danh             |                100%           |     |"<<endl;
        cout <<"|       |------------------------|-----------------------------------|-------------------------------|     |"<<endl;
        cout <<"|       |    19119007            |         Pham Thien Phuc           |                100%           |     |"<<endl;
        cout <<"|       |------------------------|-----------------------------------|-------------------------------|     |"<<endl;
        cout <<"|       |    19119009            |         Nguyen Nhat Long          |                100%           |     |"<<endl;
        cout <<"|        ============================================================================================      |"<<endl;
        cout <<"|                                                                                                          |"<<endl;
        cout <<"|                                                                                                          |"<<endl;
        cout <<"|                                                                                                          |"<<endl;
        cout <<"|                                                                                                          |"<<endl;
        cout <<"|           GIANG VIEN HUONG DAN: PGS.TS HOANG VAN DUNG                                                    |"<<endl;
        cout <<"|                                                                                                          |"<<endl;
        cout <<"|                                                                                                          |"<<endl;
        cout <<"|                                                                                                          |"<<endl;
        cout <<"|                                                                                                          |"<<endl;
        cout <<" =========================================================================================================="<<endl;

        cout <<"            ______________________________________________________"<<endl;
        cout <<"           |   Chao mung quy khach den voi cua hang quan ao UTE   |"<<endl;
        cout <<"           |      Chuyen: Quan ao cac loai Thun, Short, Jean      |"<<endl;
        cout <<"           |______________________________________________________|"<<endl;
        cout <<"           |                   Cac yeu cau:                       |"<<endl;
        cout <<"           |______________________________________________________|"<<endl;
        cout <<"           |     |                                                |"<<endl;
        cout <<"           |  1  |              Nhap hang                         |"<<endl; 
        cout <<"           |_____|________________________________________________|"<<endl;
        cout <<"           |     |                                                |"<<endl;
        cout <<"           |  2  |              In danh sach ton kho              |"<<endl;
        cout <<"           |_____|________________________________________________|"<<endl;
        cout <<"           |     |                                                |"<<endl;
        cout <<"           |  3  |              Khach hang                        |"<<endl;
        cout <<"           |_____|________________________________________________|"<<endl;
        cout <<"           |     |                                                |"<<endl;
        cout <<"           |  4  |              Xuat tong doanh thu               |"<<endl;
        cout <<"           |_____|________________________________________________|"<<endl;
        cout <<"           |     |                                                |"<<endl;
        cout <<"           |  5  |              San pham ban chay nhat            |"<<endl;
        cout <<"           |_____|________________________________________________|"<<endl;
        cout <<"           |     |                                                |"<<endl;
        cout <<"           |  6  |              In ra tong cac hoa don            |"<<endl;
        cout <<"           |_____|________________________________________________|"<<endl;
        cout <<"           |     |                                                |"<<endl;
        cout <<"           |  7  |              Nhap hang thu cong                |"<<endl;
        cout <<"           |_____|________________________________________________|"<<endl;
        cout <<"           |     |                                                |"<<endl;
        cout <<"           |  0  |              Ket thuc                          |"<<endl;
        cout <<"           |_____|________________________________________________|"<<endl;
        cout <<"\n\n ==============================";
        cout <<"Vui long chon yeu cau: ";
        cin >> luachon;
        if ((luachon < 0) || (luachon > 7)){
            cout <<"Lua chon khong hop le, vui long nhap lai\n";
            system("pause");
        } else if (luachon == 1)
        {
            filein.open("SANPHAM.TXT");
            Doc_file(filein, phantu, T); 
            cout <<"\n\n Hang da duoc nhap thanh cong \n";
            system("pause");
            filein.close();
        } else if (luachon == 2){
            cout << "\n              =======================Danh sach ton kho========================"<<endl; 
            cout <<"\n ==================================================================================================="<<endl; 
            cout <<setw(10)<<left<<"|   MSSP    |"<<setw(20)<<left<<"   Loai    |"<<setw(25)<<left<<"Ten san pham       |"<<setw(15)<<left<<"So luong    |"<<setw(15)<<left<<"   Ngay nhap    |"<<setw(15)<<left<<"   Gia    |"<<endl;  
            cout <<" ==================================================================================================="<<endl;     
            Danhsachsanpham(T);
            cout <<" ==================================================================================================="<<endl; 
            cout <<"\n";
            system("pause");
        } else if (luachon == 3){ 
            TreeNode* Buy = NULL;
            int tong = 0;
            while (true){
                system("cls");
                cout << "\n         =======================Danh sach cac san pham trong cua hang========================"<<endl; 
                cout <<"\n ==================================================================================================="<<endl; 
                cout <<setw(10)<<left<<"|   MSSP    |"<<setw(20)<<left<<"   Loai    |"<<setw(25)<<left<<"Ten san pham       |"<<setw(15)<<left<<"So luong    |"<<setw(15)<<left<<"   Ngay nhap    |"<<setw(15)<<left<<"   Gia    |"<<endl;  
                cout <<" ==================================================================================================="<<endl;      
                Danhsachsanpham(T);
                cout <<" ==================================================================================================="<<endl; 
                cout <<"\n";
                cout <<"\nQuy khach muon thuc hien yeu cau nao: ";
                cout << "\n1. Mua hang";
                cout << "\n2. Tim kiem san pham";
                cout << "\n3. Xuat hoa don";   
                cout << "\n4. Quay lai";  
                cout <<"\nVui long quy khach chon yeu cau: ";
                cin >> yeucau;  
                cin.ignore();
                    if ((yeucau < 1) || (yeucau > 4)){
                        cout <<"Lua chon khong hop le, de nhap lai vui long an phim bat ky 2 lan\n";
                        cin.ignore();
                    } else if (yeucau == 1){
                        cout << "\n\tVui long nhap MSSP cua san pham ma ban muon mua: ";
                        cin >> MSSP;
                        TreeNode *E = Timkiem(T, MSSP);
                        if (E == NULL){
                            cout <<"\n\t\tSan pham khong co trong cua hang\n";
                        } else if (E->data.Soluong == 0){
                            cout <<"\n\tSan pham ma khach hang chon da het hang\n";
                        } else if (E->data.Soluong != 0){
                            soluong = 0;
                            while (soluong == 0){   
                                cout << "\n\t\tVui long nhap so luong: ";
                                cin >> soluong;
                            }
                            if (E->data.Soluong < soluong){
                                cout <<"\n\t\tSan pham khong du so luong\n";
                            } else if (E->data.Soluong >= soluong){
                                E->data.Soluong = E->data.Soluong - soluong;
                                phantu = E->data;
                                phantu.Soluong = soluong;
                                tong = tong + (phantu.Gia * phantu.Soluong);
                                add(Buy, phantu);
                                addNum(Quanly, phantu);
                                cout <<"\n\t\tSan pham da duoc them vao gio hang\n";
                            }
                        }
                    } else if (yeucau == 2){
                        while (true){
                            system("cls");
                            cout << "\n         =======================Danh sach cac san pham trong cua hang========================"<<endl; 
                            cout <<"\n ==================================================================================================="<<endl; 
                            cout <<setw(10)<<left<<"|   MSSP    |"<<setw(20)<<left<<"   Loai    |"<<setw(25)<<left<<"Ten san pham       |"<<setw(15)<<left<<"So luong    |"<<setw(15)<<left<<"   Ngay nhap    |"<<setw(15)<<left<<"   Gia    |"<<endl;  
                            cout <<" ==================================================================================================="<<endl;      
                            Danhsachsanpham(T);
                            cout <<" ==================================================================================================="<<endl;
                            cout << "\n\tBan dang muon tim kiem san phan nao: ";
                            cout << "\n\t\t1. Tim kiem theo MSSP";
                            cout << "\n\t\t2. Tim kiem theo loai san pham (Thun, Short, Jean)";
                            cout << "\n\t\t3. Tim kiem theo ten san pham";
                            cout << "\n\t\t4. Tim kiem gia cua san pham (Tu gia chi dinh den gia thap nhat)";
                            cout << "\n\t\t5. Quay lai";
                            cout <<"\n\n\tVui long chon cach tim kiem: ";  
                            cin >> timkiem;
                            cin.ignore(); 
                            if ((timkiem < 1) || (timkiem > 5)){
                                cout <<"\tLua chon khong hop le, vui long nhap lai\n";
                                system("pause");
                            } else if (timkiem == 1){
                                cout <<"Nhap MSSP muon tim kiem: "; 
                                cin >> find;
                                cin.ignore();
                                cout << "\n=======================Danh sach cac san pham co ma san pham la "<<find<<" trong cua hang========================"<<endl;
                                cout <<"\n ==================================================================================================="<<endl; 
                                cout <<setw(10)<<left<<"|   MSSP    |"<<setw(20)<<left<<"   Loai    |"<<setw(25)<<left<<"Ten san pham       |"<<setw(15)<<left<<"So luong    |"<<setw(15)<<left<<"   Ngay nhap    |"<<setw(15)<<left<<"   Gia    |"<<endl;  
                                cout <<" ==================================================================================================="<<endl;   
                                TimkiemMSSP(T, find);
                                cout <<" ==================================================================================================="<<endl;
                                cout <<"\n";    
                                system("pause");
                            } else if (timkiem == 2){
                                cout <<"Nhap loai san pham muon tim kiem: ";
                                cin >> find; 
                                cout << "\n=======================Danh sach cac san pham co loai la "<<find<<" trong cua hang========================"<<endl;
                                cout <<"\n ==================================================================================================="<<endl; 
                                cout <<setw(10)<<left<<"|   MSSP    |"<<setw(20)<<left<<"   Loai    |"<<setw(25)<<left<<"Ten san pham       |"<<setw(15)<<left<<"So luong    |"<<setw(15)<<left<<"   Ngay nhap    |"<<setw(15)<<left<<"   Gia    |"<<endl;  
                                cout <<" ==================================================================================================="<<endl;   
                                TimkiemLoai(T, find);
                                cout <<" ==================================================================================================="<<endl;
                                cout <<"\n";
                                system("pause");
                            } else if (timkiem == 3){
                                cout <<"Nhap ten san pham muon tim kiem: ";
                                getline(cin, find);
                                cout << "\n=======================Danh sach cac san pham co ten la "<<find<<" trong cua hang========================"<<endl;
                                cout <<"\n ==================================================================================================="<<endl; 
                                cout <<setw(10)<<left<<"|   MSSP    |"<<setw(20)<<left<<"   Loai    |"<<setw(25)<<left<<"Ten san pham       |"<<setw(15)<<left<<"So luong    |"<<setw(15)<<left<<"   Ngay nhap    |"<<setw(15)<<left<<"   Gia    |"<<endl;  
                                cout <<" ==================================================================================================="<<endl;  
                                TimkiemTen(T, find);
                                cout <<" ==================================================================================================="<<endl; 
                                cout <<"\n";
                                system("pause");
                            } else if (timkiem == 4){
                                cout <<"Nhap gia san pham muon tim kiem: ";
                                cin >> gia;
                                cout << "\n=======================Danh sach cac san pham co gia tu "<<gia<<" tro xuong trong cua hang========================"<<endl;
                                cout <<"\n ==================================================================================================="<<endl; 
                                cout <<setw(10)<<left<<"|   MSSP    |"<<setw(20)<<left<<"   Loai    |"<<setw(25)<<left<<"Ten san pham       |"<<setw(15)<<left<<"So luong    |"<<setw(15)<<left<<"   Ngay nhap    |"<<setw(15)<<left<<"   Gia    |"<<endl;  
                                cout <<" ==================================================================================================="<<endl; 
                                TimkiemGia(T, gia);
                                cout <<" ==================================================================================================="<<endl; 
                                cout <<"\n";    
                                system("pause");
                            } else if (timkiem == 5){ 
                                break;
                            }    
                        } 
                    } else if (yeucau == 3){
                        tongdoanhthu = tongdoanhthu + tong;
                        cout << "\nNhan vien xuat hoat don: ";
                        getline(cin, nhanvien);
                        cout << "\n=======================Tong don hang cua quy khach========================"<<endl;
                        cout <<"\n ==================================================================================================="<<endl; 
                        cout <<setw(10)<<left<<"|   MSSP    |"<<setw(20)<<left<<"   Loai    |"<<setw(25)<<left<<"Ten san pham       |"<<setw(15)<<left<<"So luong    |"<<setw(15)<<left<<"   Ngay nhap    |"<<setw(15)<<left<<"   Gia    |"<<endl;  
                        cout <<" ==================================================================================================="<<endl; 
                        Danhsachsanpham(Buy);
                        cout <<" ==================================================================================================="<<endl;
                        cout <<"\n\n"<<setw(10)<<left<<"Tong: "<<setw(20)<<left<<setw(25)<<left<<setw(15)<<left<<setw(15)<<left<<setw(15)<<left<<tong;
                        cout << "\n\nNhan vien xuat don: "<<nhanvien;
                        cout <<"\n\n";
                        fileout << "\n---------------------------------------------------------------------------"<<endl;
                        i++;  
                        fileout <<"\t\t\tDon hang " << i<<endl;
                        fileout <<"\n";
                        fileout <<"\n ==================================================================================================="<<endl; 
                        fileout <<setw(10)<<left<<"|   MSSP    |"<<setw(20)<<left<<"   Loai    |"<<setw(25)<<left<<"Ten san pham       |"<<setw(15)<<left<<"So luong    |"<<setw(15)<<left<<"   Ngay nhap    |"<<setw(15)<<left<<"   Gia    |"<<endl;  
                        fileout <<" ==================================================================================================="<<endl;
                        Xuatfile_TXT(Buy, fileout);
                        fileout <<" ==================================================================================================="<<endl;
                        fileout << "\n\nNhan vien xuat don: "<<nhanvien<<endl;
                        fileout << "\nTong: "<< tong<<endl;
                        fileout << "\n---------------------------------------------------------------------------"<<endl;
                        Buy = NULL;
                        tong = 0;
                    } else if (yeucau == 4) {
                            break;
                    }
                    system("pause");
            }
        }else if (luachon == 4){
            cout <<"Tong doanh thu la: "<<tongdoanhthu<<endl;
            system("pause");
        }else if (luachon == 6){
            filein.open("DANHSACH.TXT", ios::in);
            while(getline(filein, str)){
                cout <<str<<endl;
            }
            filein.close();
            cout <<"Tong doanh thu la: "<<tongdoanhthu<<endl;
            system("pause");
        } else if (luachon == 5){
            TreeNode *Y = MaxofRight(Quanly);
            cout << "\n=======================San pham ban chay nhat========================"<<endl;
            cout <<"\n ==================================================================================================="<<endl; 
            cout <<setw(10)<<left<<"|   MSSP    |"<<setw(20)<<left<<"   Loai    |"<<setw(25)<<left<<"Ten san pham       |"<<setw(15)<<left<<"So luong    |"<<setw(15)<<left<<"   Ngay nhap    |"<<setw(15)<<left<<"   Gia    |"<<endl;  
            cout <<" ==================================================================================================="<<endl;
            TimkiemSoluong(Quanly, Y->data.Soluong);
            cout <<" ==================================================================================================="<<endl;
            cout << endl;
            system("pause");
        }else if (luachon == 7){
            Sanpham sanpham;
            cin.ignore();
            Nhapthongtin(sanpham);
            add(T,sanpham);
        }
        else if (luachon == 0){
            cout << "\n=========EXIT=========="<<endl;
            break;   
        }
    }
    fileout.close(); 
    return 0;
}
