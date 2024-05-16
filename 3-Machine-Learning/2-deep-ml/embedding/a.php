if (preg_match("/^\w{8,20}$/", $_GET['username'], $matches))
{
   $result = mysqli_query($conn, "SELECT * FROM users  WHERE username=$matches[0]");
}
else 
{
  echo "username 输入异常";
}
