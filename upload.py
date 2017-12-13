import requests
import os

print('\n***数据与算法 GitHub自动上传脚本***\n')
username = input('输入你在GitHub上的用户名，如 Robert Ying：')
email = input('输入你注册GitHub用的Email：')

print('\n开始配置Git...')
os.system('git config --global user.name "' + username + '"')
os.system('git config --global user.email ' + email)

print('\n你输入的信息如下：')
os.system('git config user.name')
os.system('git config user.email')

if input('\n信息正确则输入y继续，直接回车则重新输入用户名与Email：') != 'y':
    username = input('输入你在GitHub上的用户名，如 Robert Ying：')
    email = input('输入你注册GitHub用的Email：')
    print('\n你输入的信息如下：')
    os.system('git config user.name')
    os.system('git config user.email')

url = input(
    '\n输入你fork后自己对应仓库的url，如https://github.com/robertying/data-and-algorithms.git，注意！最后有".git"：')
name = input('\n输入你的真实姓名：')
payload = {"username": input('输入你的OJ用户名：'), "password": input('输入你的OJ密码：')}
print()

response = requests.post(
    'http://lambda.ee.tsinghua.edu.cn/api/auth/login/', data=payload)
answer = requests.get('http://lambda.ee.tsinghua.edu.cn/api/my/submits/', headers={
                      'Authorization': 'TOKEN ' + response.json()['auth_token']}, params={'page': 1, 'page_size': 1})
count = answer.json()['count']
answer = requests.get('http://lambda.ee.tsinghua.edu.cn/api/my/submits/', headers={
                      'Authorization': 'TOKEN ' + response.json()['auth_token']}, params={'page': 1, 'page_size': count})
results = answer.json()['results']

if not os.path.exists('data-and-algorithms'):
    os.system('git clone ' + url)
else:
    os.system('cd data-and-algorithms & git pull')
os.system('cd data-and-algorithms & git remote add upstream https://github.com/ee64/data-and-algorithms.git & git fetch upstream & git checkout master & git merge upstream/master')
problem_dir = os.listdir('./data-and-algorithms')

already_walked_results = []
for result in results:
    if result['problem_title'] not in already_walked_results and result['problem_title'] in problem_dir:
        if result['score'] == 100:
            if not os.path.exists('./data-and-algorithms/' + result['problem_title'] + '/' + name):
                os.mkdir('./data-and-algorithms/' +
                         result['problem_title'] + '/' + name)

                with open('./data-and-algorithms/' + result['problem_title'] + '/' + name + '/README.md', 'w', encoding='utf-8') as md:
                    md.write('# ' + result['problem_title'] + '\n\n')
                    md.write(
                        '| #          | 时间                           | 内存                           |\n')
                    md.write(
                        '|:----------:|:------------------------------:|:------------------------------:|\n')

                    run_results = results[0]['run_results']
                    for i in range(len(run_results)):
                        md.write(
                            '|' + str(i + 1) + '|' + str(run_results[i][1]) + ' ms|' + str(run_results[i][2]) + ' KB|\n')

                with open('./data-and-algorithms/' + result['problem_title'] + '/' + name + '/source.cpp', 'w', encoding='utf-8') as source:
                    source.write(result['code'] + '\n')

                os.system('cd data-and-algorithms & git add .')
                os.system('cd data-and-algorithms & git commit -m "Initial commit to ' +
                          result['problem_title'] + ' by ' + name)
                already_walked_results.append(result['problem_title'])
                continue

os.system('cd data-and-algorithms & git push origin master')
input('\n上传完成！如果发现没有效果，那么请重新再试一遍。回车退出程序：')
