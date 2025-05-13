import java.text.NumberFormat;
import java.util.*;

public class TaiXiu {
    public static void main(String[] args) {
        double taiKhoanNguoiChoi = 5000000.99;
        Scanner sc = new Scanner(System.in);

        Locale lc = new Locale("en", "US"); 
        NumberFormat numf = NumberFormat.getCurrencyInstance(lc);
        int luaChon = 0;
        do {
            System.out.println("----------- MỜI BẠN LỰA CHỌN -----------");
            System.out.println("Chọn (1) để tiếp tục chơi.");
            System.out.println("Chọn (phím bất kỳ khác 1) để thoát."); 
            if (sc.hasNextInt()) {
                luaChon = sc.nextInt();
            } else {
                System.out.println("Lựa chọn không hợp lệ, thoát game.");
                sc.next(); 
                luaChon = 0; 
            }


            if (luaChon == 1) {
                System.out.println("\n*** BẮT ĐẦU CHƠI: ***");
                System.out.println("****** Tài khoản của bạn: " + numf.format(taiKhoanNguoiChoi) + " ******");

                double datCuoc = 0;
                do {
                    System.out.print("****** Bạn muốn cược bao nhiêu? (Nhập số tiền > 0 và <= tài khoản của bạn): ");
                    if (sc.hasNextDouble()) {
                        datCuoc = sc.nextDouble();
                        if (datCuoc <= 0) {
                            System.out.println("****** Số tiền đặt cược phải lớn hơn 0. Vui lòng nhập lại.");
                        } else if (datCuoc > taiKhoanNguoiChoi) {
                            System.out.println("****** Số tiền đặt cược không được vượt quá tài khoản của bạn. Vui lòng nhập lại.");
                        }
                    } else {
                        System.out.println("****** Giá trị nhập không hợp lệ. Vui lòng nhập một số.");
                        sc.next(); 
                        datCuoc = -1; 
                    }
                } while (datCuoc <= 0 || datCuoc > taiKhoanNguoiChoi);

                int luaChonTaiXiu = 0;
                do {
                    System.out.print("****** Chọn: 1 <-> Tài hoặc 2 <-> Xỉu: ");
                    if (sc.hasNextInt()){
                        luaChonTaiXiu = sc.nextInt();
                        if (luaChonTaiXiu != 1 && luaChonTaiXiu != 2) {
                            System.out.println("****** Lựa chọn không hợp lệ. Vui lòng chọn 1 hoặc 2.");
                        }
                    } else {
                        System.out.println("****** Giá trị nhập không hợp lệ. Vui lòng nhập một số.");
                        sc.next(); 
                        luaChonTaiXiu = 0; 
                    }
                } while (luaChonTaiXiu != 1 && luaChonTaiXiu != 2);

                Random xucXacGenerator = new Random(); 
                int giaTri1 = xucXacGenerator.nextInt(6) + 1; 
                int giaTri2 = xucXacGenerator.nextInt(6) + 1; 
                int giaTri3 = xucXacGenerator.nextInt(6) + 1; 
                int tong = giaTri1 + giaTri2 + giaTri3;

                System.out.println("\n****** Kết quả lắc xúc xắc: " + giaTri1 + " - " + giaTri2 + " - " + giaTri3 + " ******");
                System.out.println("****** Tổng là: " + tong + " ******");

                boolean ketQuaLaTai = false; 
                if (tong >= 11 && tong <= 17) { 
                    ketQuaLaTai = true;
                    System.out.println("****** Kết quả: TÀI ******");
                } else if (tong >= 4 && tong <= 10) { // Xỉu từ 4-10
                    ketQuaLaTai = false;
                    System.out.println("****** Kết quả: XỈU ******");
                }
                 if (tong == 3 || tong == 18) {
                    taiKhoanNguoiChoi -= datCuoc;
                    System.out.println("****** NHÀ CÁI ĂN HẾT (Bộ ba đồng nhất), bạn đã thua! ******");
                } else if ((luaChonTaiXiu == 1 && ketQuaLaTai) || (luaChonTaiXiu == 2 && !ketQuaLaTai)) {
                    System.out.println("****** BẠN ĐÃ THẮNG CƯỢC! ******");
                    taiKhoanNguoiChoi += datCuoc;
                } else {
                    System.out.println("****** BẠN ĐÃ THUA CƯỢC! ******");
                    taiKhoanNguoiChoi -= datCuoc;
                }
                System.out.println("****** Tài khoản của bạn hiện là: " + numf.format(taiKhoanNguoiChoi) + " ******\n");

                if (taiKhoanNguoiChoi <=0) {
                    System.out.println("Rất tiếc, bạn đã hết tiền!");
                    luaChon = 0; 
                }

            } else if (luaChon !=0) { 
                 System.out.println("Lựa chọn không hợp lệ, thoát game.");
                 luaChon = 0; 
            }

        } while (luaChon == 1);

        System.out.println("Cảm ơn bạn đã tham gia trò chơi!");
        sc.close();
    }
}