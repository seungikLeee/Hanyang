<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="user.UserDAO" %>
<%@ page import="user.User" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="java.io.PrintWriter" %>
<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html"; charset="UTF-8">
  <title>show userInfo</title>
</head>
<body>
<h3 style="test-align: center;">내 정보</h3>
<div class="container">
  <div class="row">
    <table class="table" width ="750" style="text-align: center; border: 1px solid #dddddd">
      <thead>
      <tr>
        <th style="text-align: center;">         </th>
        <th style="text-align: center;">  아이디  </th>
        <th style="text-align: center;">  비밀번호  </th>
        <th style="text-align: center;">  이름  </th>
        <th style="text-align: center;">  성별  </th>
        <th style="text-align: center;">  이메일  </th>
        <th style="text-align: center;">  </th>
      </tr>

      </thead>
      <tbody>
      <%
        UserDAO userDAO = new UserDAO();

        String SuserID = null;
        int userID = 0;

        if(session.getAttribute("userID") != null)
        {
          SuserID = (String) session.getAttribute("userID");
          userID = Integer.parseInt(SuserID);
        }

        ArrayList<User> list = userDAO.showUser(userID);

        for(int i = 0; i < list.size(); i++) {
      %>

      <tr>
        <td><%= (i + 1)%></td>
        <td><%= list.get(i).getUserID()%></td>
        <td><%= list.get(i).getUserPassword()%></td>
        <td><%= list.get(i).getUserName()%></td>
        <td><%= list.get(i).getUserGender()%></td>
        <td><%= list.get(i).getUserEmail()%></td>
        <td>
          <input type="checkbox">
        </td>
      </tr>

      <%
        }
      %>

      </tbody>
    </table>
  </div>
</div>


</body>
</html>