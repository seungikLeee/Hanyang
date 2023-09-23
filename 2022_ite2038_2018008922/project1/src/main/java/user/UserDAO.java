package user;

import java.sql.*;
import java.util.ArrayList;

public class UserDAO {
    private Connection conn;
    private PreparedStatement pstmt;
    private ResultSet rs;

    public UserDAO()
    {
        try{
            String dbURL = "jdbc:mysql://localhost:3307/db2018008922?useUnicode=true&characterEncoding=UTF-8&allowPublicKeyRetrieval=true&serverTimezone=Asia/Seoul";
            String dbID = "root";
            String dbPassword = "nana2029**";
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(dbURL, dbID, dbPassword);

        } catch (Exception e){
            e.printStackTrace();
        }
    }

    public String test(String userID, String userPassword)
    {
        String test = userID + " " + userPassword;

        return test;
    }

    public int login(String userID, String userPassword)
    {
        String SQL = "SELECT userPassword FROM USER WHERE userID = ?";
        try{

            pstmt = conn.prepareStatement(SQL);
            pstmt.setString(1, userID);
            rs = pstmt.executeQuery();
            if(rs.next())
            {
                if(rs.getString(1).equals(userPassword))
                {
                    return 1; //로그인 성공
                }
                else
                {
                    return 0; //비밀번호 불일치
                }
            }
            return -1; // 아이디가 없음
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -2; // 데이터베이스 오류
    }

    public int adminLogin(String adminID, String adminPassword)
    {
        String SQL = "SELECT adminPassword FROM ADMIN WHERE adminID = ?";
        try{

            pstmt = conn.prepareStatement(SQL);
            pstmt.setString(1, adminID);
            rs = pstmt.executeQuery();
            if(rs.next())
            {
                if(rs.getString(1).equals(adminPassword))
                {
                    return 1; //로그인 성공
                }
                else
                {
                    return 0; //비밀번호 불일치
                }
            }
            return -1; // 아이디가 없음
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -2; // 데이터베이스 오류
    }


    public int join(User user)
    {
    	String SQL = "INSERT INTO USER VALUES (?, ?, ?, ?, ?)";
    	try
    	{
    		pstmt = conn.prepareStatement(SQL);
    		pstmt.setString(1, user.getUserID());
    		pstmt.setString(2, user.getUserPassword());
    		pstmt.setString(3, user.getUserName());
    		pstmt.setString(4, user.getUserGender());
    		pstmt.setString(5, user.getUserEmail());
    		return pstmt.executeUpdate();
    	} catch (Exception e) {
    		e.printStackTrace();
    	}
    	return -1; // 데이터베이스 오류
    }

    public ArrayList<User> showAll()
    {
        String SQL = "SELECT * FROM USER";
        ArrayList<User> studentList = new ArrayList<User>();
        try
        {
            pstmt = conn.prepareStatement(SQL);
            rs = pstmt.executeQuery();

            while(rs.next())
            {
                User user = new User();
                user.setUserID(rs.getString(1));
                user.setUserPassword(rs.getString(2));
                user.setUserName(rs.getString(3));
                user.setUserGender(rs.getString(4));
                user.setUserEmail(rs.getString(5));
                studentList.add(user);
            }

        } catch (Exception e)
        {
            e.printStackTrace();
        }
        return studentList;
    }

    public ArrayList<User> showUser(int userID)
    {
        String SQL = "SELECT * FROM USER WHERE userID = ?";
        ArrayList<User> userList = new ArrayList<User>();
        try
        {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, userID);
            rs = pstmt.executeQuery();

            while(rs.next())
            {
                User user = new User();
                user.setUserID(rs.getString(1));
                user.setUserPassword(rs.getString(2));
                user.setUserName(rs.getString(3));
                user.setUserGender(rs.getString(4));
                user.setUserEmail(rs.getString(5));
                userList.add(user);
            }

        } catch (Exception e)
        {
            e.printStackTrace();
        }
        return userList;
    }

    public int search(int classID, String courseID, String Name) {
        //3가지 모두 입력
        if (classID != 0 && courseID != null && Name != null) {
            String SQL = "SELECT * FROM CLASS WHERE class_id = ? and course_id = ? and name LIKE ?";
            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setInt(1, classID);
                pstmt.setString(2,courseID);
                pstmt.setString(3,"%" + Name + "%");
                rs = pstmt.executeQuery();

                if (rs.next()) {
                    return 1;
                } // 존재
                else
                    return 0;
                // 존재x
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        //수업번호, 학수번호 입력
        if (classID != 0 && courseID != null && Name == null) {
            String SQL = "SELECT * FROM CLASS WHERE class_id = ? and course_id = ?";
            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setInt(1, classID);
                pstmt.setString(2,courseID);
                rs = pstmt.executeQuery();

                if (rs.next()) {
                    return 2;
                }// 존재
                else
                    return 0;
                // 존재x
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        // 수업번호, 교과목명 입력
        if (classID != 0 && courseID == null && Name != null) {
            String SQL = "SELECT * FROM CLASS WHERE class_id = ? and name like ?";
            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setInt(1, classID);
                pstmt.setString(2,"%" + Name + "%");
                rs = pstmt.executeQuery();

                if (rs.next()) {
                    return 3;
                }//존재
                else
                    return 0;
                // 존재x
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        //학수번호, 교과목명 입력
        if (classID == 0 && courseID != null && Name != null) {
            String SQL = "SELECT * FROM CLASS WHERE course_id = ? and name like ?";
            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setString(1, courseID);
                pstmt.setString(2, "%"+ Name + "%");
                rs = pstmt.executeQuery();

                if (rs.next()) {
                    return 4;
                }// 존재
                else
                    return 0;
                // 존재x
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        //수업번호만 입력
        if (classID != 0 && courseID == null && Name == null) {
            String SQL = "SELECT * FROM CLASS WHERE class_id = ? ";
            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setInt(1, classID);
                rs = pstmt.executeQuery();

                if (rs.next()) {
                    return 5;
                } // 존재
                else
                    return 0;
                // 존재x
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        //학수번호만 입력
        if (classID == 0 && courseID != null && Name == null) {
            String SQL = "SELECT * FROM CLASS WHERE course_id = ? ";
            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setString(1, courseID);
                rs = pstmt.executeQuery();

                if (rs.next()) {
                    return 6;
                } // 존재
                else
                    return 0;
                // 존재x
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        //교과목명만 입력
        if (classID == 0 && courseID == null && Name != null) {
            String SQL = "SELECT * FROM CLASS WHERE name like ?";

            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setString(1,"%" + Name + "%");
                rs = pstmt.executeQuery();
                if (rs.next()) {
                    return 7;
                } // 존재
                else
                    return 0;
                // 존재x
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        //3가지 모두 입력x
        if (classID == 0 && courseID == null && Name == null) {
            return 8;
        }

        return -1;
    }

    public ArrayList<ClassInfo> searchResult(int classID, String courseID, String Name, int searchCase) {
        ArrayList<ClassInfo> classInfoList = new ArrayList<ClassInfo>();
        if(searchCase == 1)
        {
            String SQL = "SELECT CLASS.*, LECTURER.name, TIME.period, TIME.begin, TIME.end, BUILDING.name " +
                    "FROM CLASS, LECTURER, TIME, BUILDING, ROOM " +
                    "WHERE BUILDING.building_id = ROOM.building_id and CLASS.room_id = ROOM.room_id and CLASS.lecturer_id = LECTURER.lecturer_id and CLASS.class_id = TIME.class_id and CLASS.class_id = ? and course_id = ? and CLASS.name like ? order by CLASS.class_id asc";
            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setInt(1, classID);
                pstmt.setString(2,courseID);
                pstmt.setString(3,"%"+ Name+"%");
                rs = pstmt.executeQuery();
                while (rs.next()) {
                    ClassInfo classinfo = new ClassInfo();
                    classinfo.setClassID(rs.getInt(1));
                    classinfo.setClassNo(rs.getInt(2));
                    classinfo.setCourseID(rs.getString(3));
                    classinfo.setName(rs.getString(4));
                    classinfo.setMajorID(rs.getInt(5));
                    classinfo.setYear((rs.getInt(6)));
                    classinfo.setCredit((rs.getInt(7)));
                    classinfo.setLectureID(rs.getInt(8));
                    classinfo.setMaxNum(rs.getInt(9));
                    classinfo.setOpened(rs.getInt(10));
                    classinfo.setRoomID(rs.getInt(11));
                    classinfo.setLecturerName(rs.getString(12));
                    classinfo.setPeriod(rs.getInt(13));
                    classinfo.setBegin(rs.getString(14));
                    classinfo.setEnd(rs.getString(15));
                    classinfo.setBuildingName(rs.getString(16));
                    classInfoList.add(classinfo);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        else if(searchCase == 2)
        {
            String SQL = "SELECT CLASS.*, LECTURER.name, TIME.period, TIME.begin, TIME.end, BUILDING.name " +
                    "FROM CLASS, LECTURER, TIME, BUILDING, ROOM " +
                    "WHERE BUILDING.building_id = ROOM.building_id and CLASS.room_id = ROOM.room_id and CLASS.lecturer_id = LECTURER.lecturer_id and CLASS.class_id = TIME.class_id and CLASS.class_id = ? and course_id = ? order by CLASS.class_id asc";

            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setInt(1, classID);
                pstmt.setString(2,courseID);
                rs = pstmt.executeQuery();
                while (rs.next()) {
                    ClassInfo classinfo = new ClassInfo();
                    classinfo.setClassID(rs.getInt(1));
                    classinfo.setClassNo(rs.getInt(2));
                    classinfo.setCourseID(rs.getString(3));
                    classinfo.setName(rs.getString(4));
                    classinfo.setMajorID(rs.getInt(5));
                    classinfo.setYear((rs.getInt(6)));
                    classinfo.setCredit((rs.getInt(7)));
                    classinfo.setLectureID(rs.getInt(8));
                    classinfo.setMaxNum(rs.getInt(9));
                    classinfo.setOpened(rs.getInt(10));
                    classinfo.setRoomID(rs.getInt(11));
                    classinfo.setLecturerName(rs.getString(12));
                    classinfo.setPeriod(rs.getInt(13));
                    classinfo.setBegin(rs.getString(14));
                    classinfo.setEnd(rs.getString(15));
                    classinfo.setBuildingName(rs.getString(16));
                    classInfoList.add(classinfo);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        else if(searchCase == 3)
        {
            String SQL = "SELECT CLASS.*, LECTURER.name, TIME.period, TIME.begin, TIME.end, BUILDING.name " +
                    "FROM CLASS, LECTURER, TIME, BUILDING, ROOM " +
                    "WHERE BUILDING.building_id = ROOM.building_id and CLASS.room_id = ROOM.room_id and CLASS.lecturer_id = LECTURER.lecturer_id and CLASS.class_id = TIME.class_id and CLASS.class_id = ? and CLASS.name like ? order by CLASS.class_id asc";

            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setInt(1, classID);
                pstmt.setString(2,"%"+ Name+"%");
                rs = pstmt.executeQuery();
                while (rs.next()) {
                    ClassInfo classinfo = new ClassInfo();
                    classinfo.setClassID(rs.getInt(1));
                    classinfo.setClassNo(rs.getInt(2));
                    classinfo.setCourseID(rs.getString(3));
                    classinfo.setName(rs.getString(4));
                    classinfo.setMajorID(rs.getInt(5));
                    classinfo.setYear((rs.getInt(6)));
                    classinfo.setCredit((rs.getInt(7)));
                    classinfo.setLectureID(rs.getInt(8));
                    classinfo.setMaxNum(rs.getInt(9));
                    classinfo.setOpened(rs.getInt(10));
                    classinfo.setRoomID(rs.getInt(11));
                    classinfo.setLecturerName(rs.getString(12));
                    classinfo.setPeriod(rs.getInt(13));
                    classinfo.setBegin(rs.getString(14));
                    classinfo.setEnd(rs.getString(15));
                    classinfo.setBuildingName(rs.getString(16));
                    classInfoList.add(classinfo);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        else if(searchCase == 4)
        {
            String SQL = "SELECT CLASS.*, LECTURER.name, TIME.period, TIME.begin, TIME.end, BUILDING.name " +
                    "FROM CLASS, LECTURER, TIME, BUILDING, ROOM " +
                    "WHERE BUILDING.building_id = ROOM.building_id and CLASS.room_id = ROOM.room_id and CLASS.lecturer_id = LECTURER.lecturer_id and CLASS.class_id = TIME.class_id and course_id = ? and CLASS.name like ? order by CLASS.class_id asc";

            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setString(1, courseID);
                pstmt.setString(2, "%" + Name + "%");
                rs = pstmt.executeQuery();
                while (rs.next()) {
                    ClassInfo classinfo = new ClassInfo();
                    classinfo.setClassID(rs.getInt(1));
                    classinfo.setClassNo(rs.getInt(2));
                    classinfo.setCourseID(rs.getString(3));
                    classinfo.setName(rs.getString(4));
                    classinfo.setMajorID(rs.getInt(5));
                    classinfo.setYear((rs.getInt(6)));
                    classinfo.setCredit((rs.getInt(7)));
                    classinfo.setLectureID(rs.getInt(8));
                    classinfo.setMaxNum(rs.getInt(9));
                    classinfo.setOpened(rs.getInt(10));
                    classinfo.setRoomID(rs.getInt(11));
                    classinfo.setLecturerName(rs.getString(12));
                    classinfo.setPeriod(rs.getInt(13));
                    classinfo.setBegin(rs.getString(14));
                    classinfo.setEnd(rs.getString(15));
                    classinfo.setBuildingName(rs.getString(16));
                    classInfoList.add(classinfo);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        else if(searchCase == 5)
        {
            String SQL = "SELECT CLASS.*, LECTURER.name, TIME.period, TIME.begin, TIME.end, BUILDING.name " +
                    "FROM CLASS, LECTURER, TIME, BUILDING, ROOM " +
                    "WHERE BUILDING.building_id = ROOM.building_id and CLASS.room_id = ROOM.room_id and CLASS.lecturer_id = LECTURER.lecturer_id and CLASS.class_id = TIME.class_id and CLASS.class_id = ? order by CLASS.class_id asc";
            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setInt(1, classID);
                rs = pstmt.executeQuery();
                while (rs.next()) {
                    ClassInfo classinfo = new ClassInfo();
                    classinfo.setClassID(rs.getInt(1));
                    classinfo.setClassNo(rs.getInt(2));
                    classinfo.setCourseID(rs.getString(3));
                    classinfo.setName(rs.getString(4));
                    classinfo.setMajorID(rs.getInt(5));
                    classinfo.setYear((rs.getInt(6)));
                    classinfo.setCredit((rs.getInt(7)));
                    classinfo.setLectureID(rs.getInt(8));
                    classinfo.setMaxNum(rs.getInt(9));
                    classinfo.setOpened(rs.getInt(10));
                    classinfo.setRoomID(rs.getInt(11));
                    classinfo.setLecturerName(rs.getString(12));
                    classinfo.setPeriod(rs.getInt(13));
                    classinfo.setBegin(rs.getString(14));
                    classinfo.setEnd(rs.getString(15));
                    classinfo.setBuildingName(rs.getString(16));
                    classInfoList.add(classinfo);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        else if (searchCase == 6)
        {
            String SQL = "SELECT CLASS.*, LECTURER.name, TIME.period, TIME.begin, TIME.end, BUILDING.name " +
                    "FROM CLASS, LECTURER, TIME, BUILDING, ROOM " +
                    "WHERE BUILDING.building_id = ROOM.building_id and CLASS.room_id = ROOM.room_id and CLASS.lecturer_id = LECTURER.lecturer_id and CLASS.class_id = TIME.class_id and course_id = ? order by CLASS.class_id asc";
            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setString(1, courseID);
                rs = pstmt.executeQuery();
                while (rs.next()){
                    ClassInfo classinfo = new ClassInfo();
                    classinfo.setClassID(rs.getInt(1));
                    classinfo.setClassNo(rs.getInt(2));
                    classinfo.setCourseID(rs.getString(3));
                    classinfo.setName(rs.getString(4));
                    classinfo.setMajorID(rs.getInt(5));
                    classinfo.setYear((rs.getInt(6)));
                    classinfo.setCredit((rs.getInt(7)));
                    classinfo.setLectureID(rs.getInt(8));
                    classinfo.setMaxNum(rs.getInt(9));
                    classinfo.setOpened(rs.getInt(10));
                    classinfo.setRoomID(rs.getInt(11));
                    classinfo.setLecturerName(rs.getString(12));
                    classinfo.setPeriod(rs.getInt(13));
                    classinfo.setBegin(rs.getString(14));
                    classinfo.setEnd(rs.getString(15));
                    classinfo.setBuildingName(rs.getString(16));
                    classInfoList.add(classinfo);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        else if(searchCase == 7)
        {
            String SQL = "SELECT CLASS.*, LECTURER.name, TIME.period, TIME.begin, TIME.end, BUILDING.name " +
                    "FROM CLASS, LECTURER, TIME, BUILDING, ROOM " +
                    "WHERE BUILDING.building_id = ROOM.building_id and CLASS.room_id = ROOM.room_id and CLASS.lecturer_id = LECTURER.lecturer_id and CLASS.class_id = TIME.class_id and CLASS.name like ? order by CLASS.class_id asc";
            try {
                pstmt = conn.prepareStatement(SQL);
                pstmt.setString(1,"%"+ Name+"%");
                rs = pstmt.executeQuery();

                while (rs.next()){
                    ClassInfo classinfo = new ClassInfo();
                    classinfo.setClassID(rs.getInt(1));
                    classinfo.setClassNo(rs.getInt(2));
                    classinfo.setCourseID(rs.getString(3));
                    classinfo.setName(rs.getString(4));
                    classinfo.setMajorID(rs.getInt(5));
                    classinfo.setYear((rs.getInt(6)));
                    classinfo.setCredit((rs.getInt(7)));
                    classinfo.setLectureID(rs.getInt(8));
                    classinfo.setMaxNum(rs.getInt(9));
                    classinfo.setOpened(rs.getInt(10));
                    classinfo.setRoomID(rs.getInt(11));
                    classinfo.setLecturerName(rs.getString(12));
                    classinfo.setPeriod(rs.getInt(13));
                    classinfo.setBegin(rs.getString(14));
                    classinfo.setEnd(rs.getString(15));
                    classinfo.setBuildingName(rs.getString(16));
                    classInfoList.add(classinfo);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return classInfoList;
    }

    public ArrayList<RegisteredCourse> showRegisteredCourses(int studentID) {
        ArrayList<RegisteredCourse> registeredCourses = new ArrayList<RegisteredCourse>();

        String SQL = "SELECT class_id " +
                "FROM REGISTEREDCOURSES " +
                "WHERE student_id = ? order by class_id asc";
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, studentID);
            rs = pstmt.executeQuery();

            while (rs.next()) {
                RegisteredCourse registeredCourse = new RegisteredCourse();
                registeredCourse.setStudentID(studentID);
                registeredCourse.setClassID(rs.getInt(1));
                registeredCourses.add(registeredCourse);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return registeredCourses;
    }

    public ArrayList<RegisteredCourse> showWantedRegisteredCourses(int studentID) {
        ArrayList<RegisteredCourse> wantedCourses = new ArrayList<RegisteredCourse>();

        String SQL = "SELECT class_id " +
                "FROM WANTEDCOURSES " +
                "WHERE student_id = ? order by class_id asc";
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, studentID);
            rs = pstmt.executeQuery();

            while (rs.next()) {
                RegisteredCourse registeredCourse = new RegisteredCourse();
                registeredCourse.setStudentID(studentID);
                registeredCourse.setClassID(rs.getInt(1));
                wantedCourses.add(registeredCourse);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return wantedCourses;
    }


    public int registerCourse(int studentID, int classID) {
        String SQL = "INSERT INTO REGISTEREDCOURSES VALUES (?, ?)";
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, studentID);
            pstmt.setInt(2, classID);

            pstmt.executeUpdate();

            return 1;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -1;
    }

    public int registerWantedCourse(int studentID, int classID) {
        String SQL = "INSERT INTO WANTEDCOURSES VALUES (?, ?)";
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, studentID);
            pstmt.setInt(2, classID);

            pstmt.executeUpdate();

            return 1;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -1;
    }
    public int dropCourse(int studentID, int classID) {
        String SQL = "DELETE FROM REGISTEREDCOURSES WHERE student_id = ? and class_id = ?";
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, studentID);
            pstmt.setInt(2, classID);

            pstmt.executeUpdate();

            return 1;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }
    public int dropWantedCourse(int studentID, int classID) {
        String SQL = "DELETE FROM WANTEDCOURSES WHERE student_id = ? and class_id = ?";
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, studentID);
            pstmt.setInt(2, classID);

            pstmt.executeUpdate();

            return 1;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }
    public int currentRegisteredNum(int classID) {
        String SQL = "SELECT count(*)" +
                "FROM REGISTEREDCOURSES,CLASS,TIME " +
                "WHERE REGISTEREDCOURSES.class_id = CLASS.class_id and CLASS.class_id = TIME.class_id and REGISTEREDCOURSES.class_id = TIME.class_id and period=1 and REGISTEREDCOURSES.class_id = ?";
        int count = 0;
        try {

            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, classID);
            rs = pstmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1);
            }
            else {
                return 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -1;
    }

    public int duplicate(int studentID, int classID) {
        String SQL = "SELECT * FROM REGISTEREDCOURSES WHERE student_id = ? and class_id = ?";
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, studentID);
            pstmt.setInt(2, classID);
            rs = pstmt.executeQuery();

            if (rs.next()) {
                return 1; // 이미 신청
            }
            else
                return 2; // 아직 신청 x
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    public int wantedDuplicate(int studentID, int classID) {
        String SQL = "SELECT * FROM WANTEDCOURSES WHERE student_id = ? and class_id = ?";
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, studentID);
            pstmt.setInt(2, classID);
            rs = pstmt.executeQuery();

            if (rs.next()) {
                return 1; // 이미 신청
            }
            else
                return 2; // 아직 신청 x
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    public int previousGrade(int studentID, String courseID) {
        String SQL = "SELECT grade FROM CREDITS WHERE CREDITS.course_id = course_id and CREDITS.student_id = student_id and student_id = ? and course_id = ?";
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, studentID);
            pstmt.setString(2, courseID);
            rs = pstmt.executeQuery();
            if (rs.next())
            {
                String grade = rs.getString(1);

                if(grade.equals("B0") ||
                        grade.equals("B+") ||
                        grade.equals("A0") ||
                        grade.equals("A+"))
                {
                    return 1; //재수강 불가
                }
                else
                    return 2; // 재수강 가능
            }
            else
                return 3; // 첫 수강
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    public int ClassMaxNum(int classID) {
        String SQL = "SELECT person_max FROM CLASS WHERE class_id = ?";
        int classMaxNum = 0;
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, classID);
            rs = pstmt.executeQuery();

            if (rs.next()) {
                classMaxNum = rs.getInt(1);
                return classMaxNum;
            }
            else
                return -1;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -2;
    }

    public int getClassCredit(int classID) {
        String SQL = "SELECT credit FROM CLASS WHERE class_id = ?";
        int classCredit = 0;
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, classID);
            rs = pstmt.executeQuery();

            if (rs.next()) {
                classCredit = rs.getInt(1);
                return classCredit;
            }
            else
                return -1;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -2;
    }
    public int getTotalCredit(int studentID) {
        String SQL = "SELECT sum(credit) " +
                "FROM REGISTEREDCOURSES,CLASS,TIME " +
                "WHERE REGISTEREDCOURSES.class_id = CLASS.class_id and CLASS.class_id = TIME.class_id and REGISTEREDCOURSES.class_id = TIME.class_id and period=1 and student_id = ?";
        int totalCredit = 0;
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, studentID);
            rs = pstmt.executeQuery();
            if (rs.next()) {
                totalCredit = rs.getInt(1);
                return totalCredit;
            }
            else
                return -1;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -2;
    }

    public int getTotalWantedCredit(int studentID) {
        String SQL = "SELECT sum(credit) " +
                "FROM WANTEDCOURSES,CLASS,TIME " +
                "WHERE WANTEDCOURSES.class_id = CLASS.class_id and CLASS.class_id = TIME.class_id and WANTEDCOURSES.class_id = TIME.class_id and period=1 and student_id = ?";
        int totalWantedCredit = 0;
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, studentID);
            rs = pstmt.executeQuery();
            if (rs.next()) {
                totalWantedCredit = rs.getInt(1);
                return totalWantedCredit;
            }
            else
                return -1;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -2;
    }

    public int deleteCourse(int classID) {
        String SQL3 = "DELETE FROM WANTEDCOURSES WHERE class_id = ?";
        try {
            pstmt = conn.prepareStatement(SQL3);
            pstmt.setInt(1, classID);

            pstmt.executeUpdate();

            return 1;
        } catch (Exception e) {
            e.printStackTrace();
        }

        String SQL2 = "DELETE FROM REGISTEREDCOURSES WHERE class_id = ?";
        try {
            pstmt = conn.prepareStatement(SQL2);
            pstmt.setInt(1, classID);

            pstmt.executeUpdate();

            return 1;
        } catch (Exception e) {
            e.printStackTrace();
        }

        String SQL = "DELETE FROM CLASS WHERE class_id = ?";
        try {
            pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, classID);

            pstmt.executeUpdate();

            return 1;
        } catch (Exception e) {
            e.printStackTrace();
        }

        return 0;
    }
}


