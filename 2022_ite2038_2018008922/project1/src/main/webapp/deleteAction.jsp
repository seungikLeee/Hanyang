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
    <title>과목 폐강 액션</title>
</head>
<body>
<%
    String SclassID = request.getParameter("classid");
    int classID = Integer.parseInt(SclassID);

    UserDAO userDAO = new UserDAO();

    int deleteResult = userDAO.deleteCourse(classID);

    if(deleteResult == 1)
    {
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('과목 폐강 성공.')");
        script.println("</script>");
        response.sendRedirect("registeredCourses.jsp");
    }
    else
    {
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('과목 폐강 실패.')");
        script.println("history.back()");
        script.println("</script>");
    }
%>
</body>
</html>