package user;

public class Administrator {
    private String AdminID;
    private String AdminPassword;
    private String AdminName;
    private String AdminGender;
    private String AdminEmail;

    public String getAdminID() {
        return AdminID;
    }
    public void setAdminID(String adminID) {
        AdminID = adminID;
    }
    public String getAdminPassword() {
        return AdminPassword;
    }
    public void setAdminPassword(String adminPassword) {
        AdminPassword = adminPassword;
    }

    public String getAdminName() { return AdminName; }

    public void setAdminName(String adminName) {
        AdminName = adminName;
    }

    public String getAdminGender() {
        return AdminGender;
    }

    public void setAdminGender(String adminGender) {
        AdminGender = adminGender;
    }

    public String getAdminEmail() {
        return AdminEmail;
    }

    public void setAdminEmail(String adminEmail) {
        AdminEmail = adminEmail;
    }
}

