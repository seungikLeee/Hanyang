package user;

public class ClassInfo {
    private int ClassID;
    private int ClassNo;
    private String CourseID;
    private String Name;
    private int MajorID;
    private int Year;
    private int Credit;
    private int LecturerID;
    private int MaxNum;
    private int Opened;
    private int RoomID;
    private String LecturerName;
    private int Period;
    private String Begin;
    private String End;
    private String BuildingName;
    public int getClassID() {
        return ClassID;
    }
    public void setClassID(int classID) {
        ClassID = classID;
    }

    public int getClassNo() {
        return ClassNo;
    }
    public void setClassNo(int classNo) {
        ClassNo = classNo;
    }
    public String getCourseID() {
        return CourseID;
    }
    public void setCourseID(String courseID) {
        CourseID = courseID;
    }

    public String getName() {
        return Name;
    }

    public void setName(String name) {
        Name = name;
    }

    public int getMajorID() {
        return MajorID;
    }
    public void setMajorID(int majorID) {
        MajorID = majorID;
    }

    public int getYear() {
        return Year;
    }

    public void setYear(int year) {
        Year = year;
    }

    public int getCredit() {
        return Credit;
    }

    public void setCredit(int credit) {
        Credit = credit;
    }

    public int getLecturerID() {
        return LecturerID;
    }
    public void setLectureID(int lecturerID) {
        LecturerID = lecturerID;
    }

    public int getMaxNum() {
        return MaxNum;
    }
    public void setMaxNum(int maxNum) { MaxNum = maxNum; }

    public int getOpened() {
        return Opened;
    }

    public void setOpened(int opened) {
        Opened = opened;
    }
    public int getRoomID() {
        return RoomID;
    }
    public void setRoomID(int roomID) {
        RoomID = roomID;
    }

    public void setLecturerName(String lecturerName) { LecturerName = lecturerName; }

    public String getLecturerName() { return LecturerName; }
    public int getPeriod() {
        return Period;
    }

    public void setPeriod(int period) {
        Period = period;
    }

    public String getBegin() {
        return Begin;
    }

    public void setBegin(String begin) {
        String week = begin.substring(9,10);
        String weeks = null;
        if (week.equals("1")){
            weeks = "월";
        }
        else if(week.equals("2")){
            weeks = "화";
        }
        else if(week.equals("3")){
            weeks = "수";
        }
        else if(week.equals("4")){
            weeks = "목";
        }
        else if(week.equals("5")){
            weeks = "금";
        }
        else if(week.equals("6")){
            weeks = "토";
        }
        String time = begin.substring(11,16);
        Begin = weeks + "요일 " + time;
    }

    public String getEnd() {
        return End;
    }

    public void setEnd(String end) {
        String time = end.substring(11,16);
        End = time;
    }

    public String getBuildingName(){
        return BuildingName;
    }

    public void setBuildingName(String buildingName){
        BuildingName = buildingName;
    }
}
