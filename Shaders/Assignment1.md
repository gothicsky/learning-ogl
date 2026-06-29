I figured out how to solve the last question but it is brute forcing it, I need to find a way to automate it. Took me a while but it is about realizing where to look and where the colors intersect, no idea as to how to make this into code that makes sense. I'm uploading this but actually I decided to directly check for equality instead of greater than so this is actually the previous version, I didn't want to have both og them together, I'll upload the new one later 

1. question

Hint: don't forget that you can access individual elements like this: out_color = vec4(v_color.r, v_color.g, v_color.b, 1);

Now as for this triangle, it is gray, so that means the Red Green and Blue components are always equal somehow right?

The hint describes the solution for getting a gray triangle? If that's the case then in the fragment shader

    out_color.rgb *= 0;
    out_color.rgb += 0.6;

To get the triangle in the image, in the vertex shader 

    if (v_color.r == 1){
        v_color *= 0;
        v_color += 1;
    }
    else{
        v_color*=0;
    }

I think I've found the true solution to the first question... In the fragment shader
    out_color = vec4(v_color.r, v_color.r, v_color.r ,1);


2. question!

in fragment shader
    out_color = vec4(v_color.r, v_color.g, v_color.g ,1);

extra: for a vertically flipped version 
    out_color = vec4(v_color.g, v_color.b, v_color.b ,1);

3.  Question 


    out_color = vec4(1 - v_color, 1);

4.  Question 

in fragment shader

void main(){


    out_color = vec4(v_color, 1);

        if (v_color.r > 0.5){
            out_color = vec4(1, 0, 0, 1);
        }
        else {
            out_color = vec4(v_color, 1);
        }

}

extra: no weights!
        if (v_color.r > v_color.b && v_color.r > v_color.g){
            out_color = vec4(1, 0, 0, 1);
        }
        else if(v_color.b > v_color.r && v_color.b > v_color.g){
            out_color = vec4(0, 1, 0, 1);
        }
        else if(v_color.g > v_color.r && v_color.g > v_color.b){
            out_color = vec4(0, 0, 1, 1);
        }
        else {
            out_color = vec4(v_color, 1);
        }

5. Question

in fragment shader

void main(){


    out_color = vec4(v_color, 1);

        if (v_color.r > 0.5){
            out_color = vec4(1, 0, 0, 1);
        }
        else if (v_color.g > 0.5){
            out_color = vec4(0, 1, 0, 1);
        }
        else if (v_color.b > 0.5){
            out_color = vec4(0, 0, 1, 1);
        }
        else {
            out_color = vec4(v_color, 1);
        }

}

6. Question 

in fragment Shader, revised soultion:

void main(){


    out_color = vec4(v_color, 1);

    out_color.rgb *= 10;
    out_color.rgb = floor(out_color.rgb);

    //out_color *= 10;


    int Odd = int(out_color.r)%2;
    Note: for some reason although floor should do the same for positive numbers, it doesn't work that way and it's not because of precedence


    if (Odd>0){
        out_color=vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else{
        out_color=vec4(1, 0, 0, 1);
        out_color *= 10;
    }

    out_color.rgb /= 10;

}


original solution:

void main(){


    out_color = vec4(v_color, 1);

    out_color.rgb *= 10;
    out_color.rgb = floor(out_color.rgb);

    if (out_color.r>8){
        out_color=vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r>7){
        out_color=vec4(1, 0, 0, 1);
        out_color *= 10;
    }
    else if (out_color.r>6){
        out_color=vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r>5){
        out_color=vec4(1, 0, 0, 1);
        out_color *= 10;
    }
    else if (out_color.r>4){
        out_color=vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r>3){
        out_color=vec4(1, 0, 0, 1);
        out_color *= 10;
    }
    else if (out_color.r>2){
        out_color=vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r>1){
        out_color=vec4(1, 0, 0, 1);
        out_color *= 10;
    }
    else if (out_color.r>0){
        out_color=vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r==0){
        out_color=vec4(1, 0, 0, 1);
        out_color *= 10;
    }


    out_color.rgb /= 10;


7. Question 

Finally a code that serves its purpose:

void main(){


    out_color = vec4(v_color, 1);

    out_color.rgb *= 10;
    out_color.rgb = floor(out_color.rgb);

    int redIsOdd = int(out_color.r)%2;
    int grnIsOdd = int(out_color.g)%2;
    int bluIsOdd = int(out_color.b)%2;

    //White

    //First Stripe
    if (redIsOdd>0 && grnIsOdd<=0 && bluIsOdd<=0){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    if (redIsOdd>0 && grnIsOdd>0 && bluIsOdd>0){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }

    //Second Stripe
    if (redIsOdd<=0 && grnIsOdd<=0 && bluIsOdd>0){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    if (redIsOdd<=0 && grnIsOdd>0 && bluIsOdd<=0){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }

    //Red
    //First Stripe
    if (redIsOdd>0 && grnIsOdd<=0 && bluIsOdd>0){
        out_color = vec4(1, 0, 0, 1);
        out_color *= 10;
    }
    if (redIsOdd>0 && grnIsOdd>0 && bluIsOdd<=0){
        out_color = vec4(1, 0, 0, 1);
        out_color *= 10;
    }

    //Second Stripe
    if (redIsOdd<=0 && grnIsOdd>0 && bluIsOdd>0){
        out_color = vec4(1, 0, 0, 1);
        out_color *= 10;
    }
    if (redIsOdd<=0 && grnIsOdd<=0 && bluIsOdd<=0){
        out_color = vec4(1, 0, 0, 1);
        out_color *= 10;
    }


    out_color.rgb /= 10;

    // // /// /// //// //// ///// /////


}


Original Horrible Solution (But I understood and derived via this so I guess it's important):

void main(){


    out_color = vec4(v_color, 1);

    out_color.rgb *= 10;
    out_color.rgb = floor(out_color.rgb);

    if (out_color.r == 9){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }


    if (out_color.r == 8 && out_color.g == 1){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 8 && out_color.b == 1){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 8){
        out_color = vec4(1,0, 0, 1);
        out_color *= 10;
    }


    if (out_color.r == 7 && out_color.g == 1 && out_color.b == 1){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 7 && out_color.g == 2){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 7 && out_color.b == 2){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 7){
        out_color = vec4(1,0, 0, 1);
        out_color *= 10;
    }


    if (out_color.r == 6 && out_color.g == 2 && out_color.b == 1){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 6 && out_color.g==1 && out_color.b==2){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 6 && out_color.g==1 && out_color.b==1){
        out_color = vec4(1, 0, 0, 1);
        out_color *= 10;
    }
    else if (out_color.r == 6 && out_color.g == 2 && out_color.b == 2){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 6 && out_color.g == 3){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 6 && out_color.b==3){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r==6){
        out_color = vec4(1,0, 0, 1);
        out_color *= 10;
    }
        if (out_color.r == 5 && out_color.g == 3 && out_color.b == 2){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 5 && out_color.g == 2 && out_color.b == 2){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 5 && out_color.g==2 && out_color.b==3){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 5 && out_color.g==2 && out_color.b==2){
        out_color = vec4(1, 0, 0, 1);
        out_color *= 10;
    }
    else if (out_color.r == 5 && out_color.g == 3 && out_color.b == 3){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 5 && out_color.g == 3 && out_color.b == 1){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 5 && out_color.g == 1 && out_color.b == 3){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 5 && out_color.g == 4){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r == 5 && out_color.b==4){
        out_color = vec4(1, 1, 1, 1);
        out_color *= 10;
    }
    else if (out_color.r==5){
        out_color = vec4(1,0, 0, 1);
        out_color *= 10;
    }

    out_color.rgb /= 10;

    // // /// /// //// //// ///// /////


}
