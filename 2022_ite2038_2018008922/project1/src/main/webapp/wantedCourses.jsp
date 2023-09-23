<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="user.UserDAO" %>
<%@ page import="java.io.PrintWriter" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="user.RegisteredCourse" %>
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
        function wantedDrop() {
            let dropList = document.getElementById('wantedRegisteredList');
            for (let i = 1; i < dropList.rows.length; i++) {
                dropList.rows[i].cells[9].onclick = function () {
                    var classid = dropList.rows[i].cells[1].innerText;
                    alert("희망수업 신청 취소합니다.");
                    document.location.href="dropWantedAction.jsp?classid=" + classid;
                }
            }
        }
    </script>

    <title>희망 수업 등록 내역</title>
</head>
<body>
<%
    String SstudentID = null;
    int studentID = 0;

    if(session.getAttribute("userID") != null) {
        SstudentID = (String) session.getAttribute("userID");
        studentID = Integer.parseInt(SstudentID);
    }

    UserDAO userDAO = new UserDAO();
%>

<div class="container">
    <div class="col">
        <table id = "userInfo" class="table" width ="1500" style="text-align: center; border: 1px solid #dddddd">
            <thead>
            <tr>
                <th style="text-align: center;"> 희망 수업 신청 내역 </th>
            </tr>

            </thead>
            <tbody>

            <tr>
                <td><%= "학번 : " + studentID %></td>
            </tr>
            </tbody>
        </table>
    </div>
</div>
<div class="container">
    <div class="row">
        <table id = "wantedRegisteredList" class="table" width ="1500" style="text-align: center; border: 1px solid #dddddd">
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
                <th style="text-align: center;">  희망 수업 신청 취소  </th>
                <th style="text-align: center;">   </th>
            </tr>

            </thead>
            <tbody>
            <%
                ArrayList<RegisteredCourse> wantedList = userDAO.showWantedRegisteredCourses(studentID);
                int j=1;
                for(int i = 0; i< wantedList.size(); i++){

                    ArrayList<ClassInfo> classList = userDAO.searchResult(wantedList.get(i).getClassID(),null,null, 5);

                    int flag = -1;
                    for(int k = 0; k < classList.size(); k++) {
                        if(k+1 < classList.size()){
                            flag = 1;
                        }
                        else{
                            flag = 0;
                        }

                        if(flag==1&&classList.get(k+1).getPeriod()==2) {
                        %>  <tr>
                                <td><%= (j)%></td>
                                <td><%= classList.get(k).getClassID()%></td>
                                <td><%= classList.get(k).getCourseID()%></td>
                                <td><%= classList.get(k).getName()%></td>
                                <td><%= classList.get(k).getCredit()%></td>
                                <td><%= classList.get(k).getLecturerName()%></td>
                                <td><%= classList.get(k).getBegin()+ " ~ " + classList.get(k).getEnd() + ", " + classList.get(k+1).getBegin()+ " ~ " + classList.get(k+1).getEnd()%></td>
                                <%
                                    int registeredNum = userDAO.currentRegisteredNum(classList.get(k).getClassID());
                                %>
                                <td><%= registeredNum + "/" + classList.get(k).getMaxNum() %></td>
                                <td><%= classList.get(k).getBuildingName() + " " + classList.get(k).getRoomID() + "호" %></td>
                                <td><button type="button" class="navyBtn" onClick="wantedDrop()">희망 수업 신청 취소</button></td>
                            </tr>
                <%
                            k++;
                        }
                        else {
                        %>  <tr>
                                <td><%= (j)%></td>
                                <td><%= classList.get(k).getClassID()%></td>
                                <td><%= classList.get(k).getCourseID()%></td>
                                <td><%= classList.get(k).getName()%></td>
                                <td><%= classList.get(k).getCredit()%></td>
                                <td><%= classList.get(k).getLecturerName()%></td>
                                <td><%= classList.get(k).getBegin()+ " ~ " + classList.get(k).getEnd()%></td>
                                <%
                                    int registeredNum = userDAO.currentRegisteredNum(classList.get(k).getClassID());
                                %>
                                <td><%= registeredNum + "/" + classList.get(k).getMaxNum() %></td>
                                <td><%= classList.get(k).getBuildingName() + " " + classList.get(k).getRoomID() + "호" %></td>
                                <td><button type="button" class="navyBtn" onClick="wantedDrop()">희망 수업 신청 취소</button></td>
                            </tr>
            <%
                        }
                        j++;
                    }
                }
            %>
            </tbody>
        </table>
    </div>
</div>

<div class="container">
    <div class="col">
        <table id = "creditSum" class="table" width ="1500" style="text-align: right; border: 1px solid #dddddd">
            <thead>
            <tr>
                <th style="text-align: right;">    총 희망 수업 신청 학점     </th>
            </tr>

            </thead>
            <tbody>
            <%
                int totalWantedCredit = userDAO.getTotalWantedCredit(studentID);
            %>
            <tr>
                <td><%= totalWantedCredit %></td>
            </tr>
            </tbody>
        </table>
    </div>
</div>
</body>
</html>