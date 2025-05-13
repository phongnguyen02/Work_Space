import java.text.NumberFormat;
import java.util.Locale;
import java.util.Random;
import java.util.Scanner;

public class TaiXiu {

    private static int layLuaChonMenu(Scanner sc) {
        System.out.println("----------- MỜI BẠN LỰA CHỌN -----------");
        System.out.println("Chọn (1) để tiếp tục chơi.");
        System.out.println("Chọn (phím bất kỳ khác 1) để thoát.");
        if (sc.hasNextInt()) {
            return sc.nextInt();
        } else {
            System.out.println("Lựa chọn không hợp lệ, tự động thoát game.");
            sc.next();
            return 0;
        }
    }

    private static double layTienCuoc(Scanner sc, double taiKhoanHienCo, NumberFormat dinhDangTien) {
        double datCuoc;
        do {
            System.out.print("****** Bạn muốn cược bao nhiêu? (Nhập số tiền > 0 và <= tài khoản của bạn): ");
            if (sc.hasNextDouble()) {
                datCuoc = sc.nextDouble();
                if (datCuoc <= 0) {
                    System.out.println("****** Số tiền đặt cược phải lớn hơn 0. Vui lòng nhập lại.");
                } else if (datCuoc > taiKhoanHienCo) {
                    System.out.println("****** Số tiền đặt cược không được vượt quá tài khoản của bạn. Vui lòng nhập lại.");
                }
            } else {
                System.out.println("****** Giá trị nhập không hợp lệ. Vui lòng nhập một số.");
                sc.next();
                datCuoc = -1;
            }
        } while (datCuoc <= 0 || datCuoc > taiKhoanHienCo);
        return datCuoc;
    }

    private static int layLuaChonTaiXiu(Scanner sc) {
        int luaChon;
        do {
            System.out.print("****** Chọn: 1 <-> Tài hoặc 2 <-> Xỉu: ");
            if (sc.hasNextInt()) {
                luaChon = sc.nextInt();
                if (luaChon != 1 && luaChon != 2) {
                    System.out.println("****** Lựa chọn không hợp lệ. Vui lòng chọn 1 hoặc 2.");
                }
            } else {
                System.out.println("****** Giá trị nhập không hợp lệ. Vui lòng nhập một số.");
                sc.next();
                luaChon = 0;
            }
        } while (luaChon != 1 && luaChon != 2);
        return luaChon;
    }

    private static int[] tungBaXucXac(Random generator) {
        return new int[]{
            generator.nextInt(6) + 1,
            generator.nextInt(6) + 1,
            generator.nextInt(6) + 1
        };
    }

    public static void main(String[] args) {
        double taiKhoanNguoiChoi = 5000000.99;
        Scanner sc = new Scanner(System.in);
        Random xucXacGenerator = new Random();

        Locale lc = new Locale("en", "US");
        NumberFormat numf = NumberFormat.getCurrencyInstance(lc);

        int luaChonMenu = 1; 
        do {
            
            if (taiKhoanNguoiChoi <= 0 && luaChonMenu == 1) { 
                System.out.println("\n*** BẠN ĐÃ HẾT TIỀN! ***");
                System.out.println("****** Tài khoản của bạn: " + numf.format(0.0) + " ******");
                System.out.println("Cảm ơn bạn đã tham gia. Hẹn gặp lại!");
                luaChonMenu = 0; 
                break; 
            }


            if (luaChonMenu == 1) { 
                 luaChonMenu = layLuaChonMenu(sc);
            }


            if (luaChonMenu == 1) {
                
                if (taiKhoanNguoiChoi <= 0) {
                    System.out.println("\n*** BẠN ĐÃ HẾT TIỀN! ***");
                    System.out.println("****** Tài khoản của bạn: " + numf.format(0.0) + " ******");
                    System.out.println("Cảm ơn bạn đã tham gia. Hẹn gặp lại!");
                    luaChonMenu = 0; 
                    break; 
                }

                System.out.println("\n*** BẮT ĐẦU CHƠI: ***");
                System.out.println("****** Tài khoản của bạn: " + numf.format(taiKhoanNguoiChoi) + " ******");

                double datCuoc = layTienCuoc(sc, taiKhoanNguoiChoi, numf);
                int luaChonTaiHayXiu = layLuaChonTaiXiu(sc);

                int[] ketQuaXucXac = tungBaXucXac(xucXacGenerator);
                int giaTri1 = ketQuaXucXac[0];
                int giaTri2 = ketQuaXucXac[1];
                int giaTri3 = ketQuaXucXac[2];
                int tong = giaTri1 + giaTri2 + giaTri3;

                System.out.println("\n****** Kết quả lắc xúc xắc: " + giaTri1 + " - " + giaTri2 + " - " + giaTri3 + " ******");
                System.out.println("****** Tổng là: " + tong + " ******");

                boolean ketQuaLaTai = false;
                if (tong >= 11 && tong <= 17) {
                    ketQuaLaTai = true;
                    System.out.println("****** Kết quả: TÀI ******");
                } else if (tong >= 4 && tong <= 10) {
                    ketQuaLaTai = false;
                    System.out.println("****** Kết quả: XỈU ******");
                }

                if (tong == 3 || tong == 18) {
                    System.out.println("****** NHÀ CÁI ĂN HẾT (Bộ ba đồng nhất), bạn đã thua! ******");
                    taiKhoanNguoiChoi -= datCuoc;
                } else if ((luaChonTaiHayXiu == 1 && ketQuaLaTai) || (luaChonTaiHayXiu == 2 && !ketQuaLaTai)) {
                    System.out.println("****** BẠN ĐÃ THẮNG CƯỢC! ******");
                    taiKhoanNguoiChoi += datCuoc;
                } else {
                    System.out.println("****** BẠN ĐÃ THUA CƯỢC! ******");
                    taiKhoanNguoiChoi -= datCuoc;
                }
                System.out.println("****** Tài khoản của bạn hiện là: " + numf.format(taiKhoanNguoiChoi) + " ******\n");

                if (taiKhoanNguoiChoi <= 0) {
                    System.out.println("Rất tiếc, bạn đã hết tiền!");
                    luaChonMenu = 0; 
                }

            } else if (luaChonMenu != 0) { 
                 System.out.println("Thoát game theo lựa chọn của bạn.");
              
            }

        } while (luaChonMenu == 1);

        System.out.println("\nCảm ơn bạn đã tham gia trò chơi!");
        sc.close();
    }
}
