<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="java.io.PrintWriter" %>
<%@ page import="user.UserDAO" %>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html"; charset="UTF-8">
    <title>메인페이지</title>
</head>
<body>
	<%
		UserDAO userDAO = new UserDAO();

		String userID = null;
		String adminID = null;

		if(session.getAttribute("userID") != null)
		{
			userID = (String) session.getAttribute("userID");
		}
		else if(session.getAttribute("adminID") != null)
		{
			adminID = (String) session.getAttribute("adminID");
		}
	%>
	<h3 style="test-align: center;">수강신청 메인페이지</h3>
	<%
		if (userID == null && adminID == null)
		{
	%>
		<button type="button" class="navyBtn" onClick="location.href='login.jsp'">학생 로그인</button>
		<button type="button" class="navyBtn" onClick="location.href='adminLogin.jsp'">관리자 로그인</button>
		<button type="button" class="navyBtn" onClick="location.href='join.jsp'">회원가입</button>

	<%		
		}
		else if(adminID != null)
		{
	%>
		<button type="button" class="navyBtn" onClick="location.href='logoutAction.jsp'">로그아웃</button>
		<button type="button" class="navyBtn" onClick="location.href='showAll.jsp'">모든 사용자 정보</button>
		<button type="button" class="navyBtn" onClick="location.href='searchAdmin.jsp'">과목 정보 검색</button>
		<button type="button" class="navyBtn" onClick="location.href='createCourse.jsp'">과목 설강</button>

	<%
		}
		else if(userID != null)
		{
	%>
		<button type="button" class="navyBtn" onClick="location.href='logoutAction.jsp'">로그아웃</button>
		<button type="button" class="navyBtn" onClick="location.href='showUser.jsp'">내 정보</button>
		<button type="button" class="navyBtn" onClick="location.href='search.jsp'">수강 편람 검색</button>
		<button type="button" class="navyBtn" onClick="location.href='registeredCourses.jsp'">수강 신청 내역</button>
		<button type="button" class="navyBtn" onClick="location.href='wantedCourses.jsp'">희망 수업 등록 내역</button>

	<%
		}
	%>
</body>
</html>