#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

class User{//base class
protected:
    string username;

public:
    void post_timeline(){};
    void view_timeline(){};

    string getUsername(){
          return username;
    };
};

class registerd:public User{
protected:
    vector<string> posts;
public:
    registerd(string &user_name){
      username=user_name;
    };
    void view_timeline(){
        cout<<username<<" timeline:"<<endl;
        if(posts.size()>0){
        for (const string& post : posts) {
            cout << " - " << post << "\n";
        }}
        else cout<<"they have no posts on their profile\n";
    }
    void post_timeline(){
        string thread;
        cout<<"what do you wanna post?:";
        getline(cin,thread);
        time_t now = time(nullptr);
        string t = ctime(&now);
        posts.push_back(thread);
    };
    string getUsername(){
        return username;
    };
    friend class admin;
};


class Platform{
    vector<registerd> users;
public:
    registerd* finduser(string& username){
        for (registerd& user : users) {
            if (user.getUsername() == username) {
                return &user;
            }
        }
        return nullptr;
    }

    void add_user(string& username){
        users.push_back(registerd(username));
    }
    friend class admin;

};

class admin:public User{
public:
    void delete_post(string user_name,string thread, Platform& app){
        registerd* user = app.finduser(user_name);
        if (user == nullptr) {
            return;
        }

        auto it = std::find(user->posts.begin(), user->posts.end(), thread);

        // If the post is not found, return.
        if (it == user->posts.end()) {
            return;
        }

        // Erase the post from the user's posts vector.
        user->posts.erase(it);
    };

    void view_timelines(Platform& app){
        for (registerd& user : app.users) {
            user.view_timeline();
            }
        };
    string getpassword(){
        return password;
    }
private:
    string password = "admin1";
    };




int main(){
    string user_name;


    Platform app;

    int choice;
    registerd *k;

    admin Admin;
    bool admin_run = false;
    bool run = true;
    string password;
    while(run){
        cout<<"What do u wish to do:\n1]ADD USER \n2]Post on Timeline \n3]View Timeline \n4]Admin Account \n5]exit \nYour Choice:";
        cin>>choice;
        switch(choice){
            case 1:
                system("clear");
                cout<<"enter username:";
                cin>>user_name;
                app.add_user(user_name);

                cout<<"user added!! please press enter to continue:";

                break;
            case 2:
                system("clear");
                cout<<"enter username:";
                cin>>user_name;
                cin.ignore();
                k=app.finduser(user_name);
                if(k){
                (*k).post_timeline();}
                else{
                    cout<<"no such user exists in database\n";
                }
                break;
            case 3:
                system("clear");
                cout<<"enter username:";
                cin>>user_name;
                k=app.finduser(user_name);
                if(k){
                    (*k).view_timeline();}
                else{
                    cout<<"no such user exists in database\n";
                }
                break;
            case 4:
                cout<<"enter your admin password:";
                cin>>password;
                if(password==Admin.getpassword()){
                    admin_run=true;
                    run=false;
                }else{
                    cout<<"invalid password!!press enter to continue...";


                }
                break;
            case 5:
                system("clear");
                cout<<"nice to see you bye";
                run = false;
                break;
        }
    }
//    string l = "moksh";
//    Admin.delete_post("moksh","hola loda",app);
//    k=app.finduser(l);
//    (*k).view_timeline();
    while(admin_run){
        system("clear");
        cout<<"YOU ARE IN ADMIN MENU NOW!!\n";
        cout<<"What do u wish to do:\n1]Delete Post of User \n2]View Timelines \n3]exit \nYour Choice:";
        cin>>choice;
        cin.ignore();
        switch (choice) {
            case 1:{
                system("clear");
                cout<<"enter the username to delete post of:";
                cin>>user_name;
                string posted_thread;
                cout<<"enter the post u want to delete:";
                cin.ignore();
                getline(cin,posted_thread);
                Admin.delete_post(user_name,posted_thread,app);
                break;}
            case 2:
                system("clear");
                Admin.view_timelines(app);
                cout<<"press enter to continue....";
                cin.ignore();
                break;
            case 3:
                admin_run=false;
                break;

        }
    }

}
