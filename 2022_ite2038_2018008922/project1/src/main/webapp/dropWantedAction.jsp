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
  <title>수강취소 액션</title>
</head>
<body>
<%
  String SclassID = request.getParameter("classid");
  int classID = Integer.parseInt(SclassID);

  String SstudentID = null;
  int studentID = 0;

  if(session.getAttribute("userID") != null) {
    SstudentID = (String) session.getAttribute("userID");
    studentID = Integer.parseInt(SstudentID);
  }

  UserDAO userDAO = new UserDAO();

  int dropWantedResult = userDAO.dropWantedCourse(studentID, classID);

  if(dropWantedResult == 1)
  {
    PrintWriter script = response.getWriter();
    script.println("<script>");
    script.println("alert('희망수업 등록 취소 성공.')");
    script.println("</script>");
    response.sendRedirect("wantedCourses.jsp");
  }
  else
  {
    PrintWriter script = response.getWriter();
    script.println("<script>");
    script.println("alert('희망 수업 등록 취소 실패.')");
    script.println("history.back()");
    script.println("</script>");
  }
%>
</body>
</html>