<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="user.UserDAO" %>
<%@ page import="user.User" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="java.io.PrintWriter" %>
<%@ page import="user.ClassInfo" %>
<% request.setCharacterEncoding("UTF-8"); %>
<jsp:useBean id="ClassInfo" class="user.ClassInfo" scope="page" />
<jsp:setProperty name="ClassInfo" property="classID" />
<jsp:setProperty name="ClassInfo" property="courseID" />
<jsp:setProperty name="ClassInfo" property="name" />
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html"; charset="UTF-8">
    <script>
        function deleteCourse() {
            let dropList = document.getElementById('course_list');
            for (let i = 1; i < dropList.rows.length; i++) {
                dropList.rows[i].cells[9].onclick = function () {
                    var classid = dropList.rows[i].cells[1].innerText;
                    alert("과목을 폐강합니다.");
                    document.location.href="deleteAction.jsp?classid=" + classid;
                }
            }
        }
    </script>
    <title>과목 정보 조회</title>
</head>
<h3 style="test-align: center;">과목 정보 조회</h3>
<body>
<%

    int classID = 0;
    String courseID = null;
    String Name = null;

    if(session.getAttribute("classID") != null)
    {
        classID = (int)session.getAttribute("classID");
    }
    if(session.getAttribute("courseID") != null)
    {
        courseID = (String) session.getAttribute("courseID");
    }
    if(session.getAttribute("name") != null)
    {
        Name = (String) session.getAttribute("name");
    }

    UserDAO userDAO = new UserDAO();

    int searchCase = userDAO.search(ClassInfo.getClassID(), ClassInfo.getCourseID(), ClassInfo.getName());

    if(searchCase >= 1) {
%>
<div class="container">
    <div class="row">
        <table id = "course_list" class="table" width ="1700" style="text-align: center; border: 1px solid #dddddd">
            <thead>
            <tr>
                <th style="text-align: center;">         </th>
                <th style="text-align: center;">  수업번호  </th>
                <th style="text-align: center;">  학수번호  </th>
                <th style="text-align: center;">  교과목명 </th>
                <th style="text-align: center;">  학점  </th>
                <th style="text-align: center;">  교강사 이름  </th>
                <th style="text-align: center;">  수업 시간  </th>
                <th style="text-align: center;">  신청 인원/수강 정원  </th>
                <th style="text-align: center;">  강의실(건물+호수) </th>
                <th style="text-align: center;">  과목 폐강 </th>
                <th style="text-align: center;">   </th>
            </tr>

            </thead>
            <tbody>
            <%
                ArrayList<ClassInfo> classList = userDAO.searchResult(ClassInfo.getClassID(), ClassInfo.getCourseID(), ClassInfo.getName(), searchCase);
                int j = 1;
                int flag = -1;
                for(int i = 0; i < classList.size(); i++) {
                    if(i+1 < classList.size()){
                        flag = 1;
                    }
                    else{
                        flag = 0;
                    }

                    if(flag==1&&classList.get(i+1).getPeriod()==2){
            %>
            <tr>
                <td><%= (j)%></td>
                <td><%= classList.get(i).getClassID()%></td>
                <td><%= classList.get(i).getCourseID()%></td>
                <td><%= classList.get(i).getName()%></td>
                <td><%= classList.get(i).getCredit()%></td>
                <td><%= classList.get(i).getLecturerName()%></td>
                <td><%= classList.get(i).getBegin()+ " ~ " + classList.get(i).getEnd() + ", " + classList.get(i+1).getBegin()+ " ~ " + classList.get(i+1).getEnd()%></td>
                <%
                    int registeredNum = userDAO.currentRegisteredNum(classList.get(i).getClassID());
                %>
                <td><%= registeredNum + "/" + classList.get(i).getMaxNum() %></td>
                <td><%= classList.get(i).getBuildingName() + " " + classList.get(i).getRoomID() + "호" %></td>
                <td><button type="button" class="navyBtn" onClick="deleteCourse()">과목 폐강</button></td>
            </tr>
            <%
                i++;
            }
            else{
            %>
            <tr>
                <td><%= (j)%></td>
                <td><%= classList.get(i).getClassID()%></td>
                <td><%= classList.get(i).getCourseID()%></td>
                <td><%= classList.get(i).getName()%></td>
                <td><%= classList.get(i).getCredit()%></td>
                <td><%= classList.get(i).getLecturerName()%></td>
                <td><%= classList.get(i).getBegin()+ " ~ " + classList.get(i).getEnd()%></td>
                <%
                    int registeredNum = userDAO.currentRegisteredNum(classList.get(i).getClassID());
                %>
                <td><%= registeredNum + "/" + classList.get(i).getMaxNum() %></td>
                <td><%= classList.get(i).getBuildingName() + " " + classList.get(i).getRoomID() + "호" %></td>
                <td><button type="button" class="navyBtn" onClick="deleteCourse()">과목 폐강</button></td>
            </tr>
            <%
                    }
                    j++;
                }
            %>
            </tbody>
        </table>
    </div>
</div>
<%
    }
    else if(searchCase == 8) {
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('조회하고자하는 교과목 정보를 입력해 주세요.')");
        script.println("history.back()");
        script.println("</script>");
    }
    else {
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('교과목이 조회되지 않습니다.')");
        script.println("history.back()");
        script.println("</script>");
    }
%>
</body>
</html>