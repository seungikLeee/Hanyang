<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html"; charset="UTF-8">
  <meta name="viewport" content="width=devoce-width", initial-scale="1">
  <link rel="stylesheet" href="css/bootstrap.css">
  <title>관리자 로그인</title>
</head>

<body>
<div class="container">
  <div class="col-lg-4"></div>
  <div class="col-lg-4">
    <div class="jumbotron" style="padding-top: 20px;">
      <form method="post" action="adminLoginAction.jsp">
        <h3 style="test-align: center;">관리자 로그인</h3>
        <div class="form-group">
          <input type="text" class="form-control" placeholder="아이디" name="adminID" maxlength="20">
        </div>
        <div class="form-group">
          <input type="password" class="form-control" placeholder="비밀번호" name="adminPassword" maxlength="20">
        </div>
        <input type="submit" class="btn btn-primary form-control" value="관리자 로그인">
      </form>
    </div>
  </div>
  <div class="col-lg-4"></div>
</div>


<script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
<script src="js/bootstrap.js"></script>
</body>
</html>