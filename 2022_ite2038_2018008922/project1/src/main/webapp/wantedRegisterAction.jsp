<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="user.UserDAO" %>
<%@ page import="java.io.PrintWriter" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="user.ClassInfo" %>
<%@ page import="user.RegisteredCourse" %>
<% request.setCharacterEncoding("UTF-8"); %>
<jsp:useBean id="ClassInfo" class="user.ClassInfo" scope="page" />
<jsp:setProperty name="ClassInfo" property="classID" />
<jsp:setProperty name="ClassInfo" property="courseID" />
<jsp:setProperty name="ClassInfo" property="name" />

<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html"; charset="UTF-8">
    <title>희망 수업 신청 액션</title>
</head>
<body>
<%
    String SclassID = request.getParameter("classid");
    int classID = Integer.parseInt(SclassID);

    String courseID = request.getParameter("courseid");

    String SstudentID = null;
    int studentID = 0;

    if(session.getAttribute("userID") != null) {
        SstudentID = (String) session.getAttribute("userID");
        studentID = Integer.parseInt(SstudentID);
    }

    UserDAO userDAO = new UserDAO();

    //중복 신청 확인
    int duplicateResult =  -1;
    int dResult=0;
    duplicateResult = userDAO.wantedDuplicate(studentID,classID);

    if(duplicateResult == 1)
    {
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('이미 희망 등록한 과목입니다.')");
        script.println("history.back()");
        script.println("</script>");
        dResult = -1;
    }
    else if(duplicateResult == 2) {
        dResult = 1;
    }
    else {
        duplicateResult = 0;
    }

    //재수강 가능 여부 확인
    int previousResult = -1;
    int pResult=0;
    previousResult = userDAO.previousGrade(studentID, courseID);

    if(previousResult == 1) {
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('이전에 B0 이상의 학점을 받은 경우 재수강이 불가능합니다.')");
        script.println("history.back()");
        script.println("</script>");
        pResult=-1;
    }
    else if(previousResult == 2) {
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('재수강 가능합니다.')");
        script.println("</script>");
        pResult=1;
    }
    else if(previousResult == 3) {
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('첫 수강입니다.')");
        script.println("</script>");
        pResult=1;
    }
    else {

    }

    if(dResult==1 && pResult==1) {
        int registerWantedResult = 0;
        registerWantedResult = userDAO.registerWantedCourse(studentID,classID);

        PrintWriter script = response.getWriter();
        if(registerWantedResult==1) {
            script.println("<script>");
            script.println("alert('희망 수업 신청 성공.')");
            script.println("history.back()");
            script.println("</script>");
        }
        else{
            script.println("<script>");
            script.println("alert('희망 수업 신청 실패.')");
            script.println("history.back()");
            script.println("</script>");
        }
    }
    else {
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('희망 수업 신청 실패.')");
        script.println("history.back()");
        script.println("</script>");
    }

%>
</body>
</html>