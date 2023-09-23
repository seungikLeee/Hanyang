<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html"; charset="UTF-8">
  <meta name="viewport" content="width=devoce-width", initial-scale="1">
  <link rel="stylesheet" href="css/bootstrap.css">
  <title>과목 정보 검색</title>
</head>

<body>
<div class="container">
  <div class="col-lg-4"></div>
  <div class="col-lg-4">
    <div class="jumbotron" style="padding-top: 20px;">
      <form method="post" action="searchAdminAction.jsp">
        <h3 style="test-align: center;">과목 정보 검색</h3>
        <div class="form-group">
          <input type="text" class="form-control" placeholder="수업번호" name="classID" maxlength="20">
        </div>
        <div class="form-group">
          <input type="text" class="form-control" placeholder="학수번호" name="courseID" maxlength="20">
        </div>
        <div class="form-group">
          <input type="text" class="form-control" placeholder="교과목명" name="name" maxlength="20">
        </div>
        <input type="submit" class="btn btn-primary form-control" value="검색">
      </form>
    </div>
  </div>
  <div class="col-lg-4"></div>
</div>


<script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
<script src="js/bootstrap.js"></script>
</body>
</html>