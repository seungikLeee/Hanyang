<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="user.UserDAO" %>
<%@ page import="java.io.PrintWriter" %>
<% request.setCharacterEncoding("UTF-8"); %>
<jsp:useBean id="administrator" class="user.Administrator" scope="page" />
<jsp:setProperty name="administrator" property="adminID" />
<jsp:setProperty name="administrator" property="adminPassword" />
<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html"; charset="UTF-8">
  <title>관리자 로그인 액션</title>
</head>
<body>
<%
  String adminID = null;
  if(session.getAttribute("adminID") != null)
  {
    adminID = (String) session.getAttribute("adminID");
  }
  if(adminID != null)
  {
    PrintWriter script = response.getWriter();
    script.println("<script>");
    script.println("alert('이미 로그인이 되어있습니다.')");
    script.println("location.href = 'main.jsp'");
    script.println("</script>");
  }

  UserDAO userDAO = new UserDAO();

  int result = userDAO.adminLogin(administrator.getAdminID(), administrator.getAdminPassword());

  if(result == 1)
  {
    session.setAttribute("adminID", administrator.getAdminID());
    PrintWriter script = response.getWriter();
    script.println("<script>");
    script.println("location.href = 'main.jsp'");
    script.println("</script>");
  }
  else if(result == 0)
  {
    PrintWriter script = response.getWriter();
    script.println("<script>");
    script.println("alert('비밀번호가 틀립니다.')");
    script.println("history.back()");
    script.println("</script>");
  }
  else if(result == -1)
  {
    PrintWriter script = response.getWriter();
    script.println("<script>");
    script.println("alert('존재하지 않는 아이디입니다.')");
    script.println("history.back()");
    script.println("</script>");
  }
  else if(result == -2)
  {
    PrintWriter script = response.getWriter();
    script.println("<script>");
    script.println("alert('데이터베이스 오류가 발생했습니다.')");
    script.println("history.back()");
    script.println("</script>");
  }

%>

</body>
</html>