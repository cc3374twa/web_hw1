# web_hw1
首先打開./testserver
用瀏覽器輸入localhost:4444 會看到網頁+圖片
![image](https://user-images.githubusercontent.com/94603586/142551691-b3029805-1eb9-4507-833c-c02f641ef4b3.png)
用另外的終端機打開./client_deliver
可以在server看到新的連線加入
![image](https://user-images.githubusercontent.com/94603586/142551716-63169a0b-721c-403a-8fac-bfabbcc003eb.png)
![image](https://user-images.githubusercontent.com/94603586/142551721-b6c5cda7-ba1a-47d3-8e36-c17adc4e9a55.png)

 
在client_deliver隨便輸入文字後enter
Deliver會將sendthisfile.txt的內容傳給server(不是傳輸入的文字)
 ![image](https://user-images.githubusercontent.com/94603586/142551734-c6be0332-2e9e-40d3-ae59-7c01053df46b.png)


然後server會把sendthisfile.txt的內容儲存成GetFileFromClient.txt
在server的terminal會顯示[+]Data written in the text file
 
![image](https://user-images.githubusercontent.com/94603586/142551742-2acab295-632b-41dc-a654-e4809435f2ea.png)

