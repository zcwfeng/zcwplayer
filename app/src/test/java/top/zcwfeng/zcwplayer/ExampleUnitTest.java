package top.zcwfeng.zcwplayer;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import org.junit.Test;

import java.io.IOException;

import static org.junit.Assert.assertEquals;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class ExampleUnitTest {
    @Test
    public void addition_isCorrect() {
        assertEquals(4, 2 + 2);
    }
//{"data":[{"name":"CCTV-1高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv1hd","phone":"http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8"},{"name":"CCTV-2高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv2hd","phone":"http://ivi.bupt.edu.cn/hls/cctv2hd.m3u8"},{"name":"CCTV-3高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv3hd","phone":"http://ivi.bupt.edu.cn/hls/cctv3hd.m3u8"},{"name":"CCTV-4高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv4hd","phone":"http://ivi.bupt.edu.cn/hls/cctv4hd.m3u8"},{"name":"CCTV-5+高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv5phd","phone":"http://ivi.bupt.edu.cn/hls/cctv5phd.m3u8"},{"name":"CCTV-6高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv6hd","phone":"http://ivi.bupt.edu.cn/hls/cctv6hd.m3u8"},{"name":"CCTV-7高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv7hd","phone":"http://ivi.bupt.edu.cn/hls/cctv7hd.m3u8"},{"name":"CCTV-8高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv8hd","phone":"http://ivi.bupt.edu.cn/hls/cctv8hd.m3u8"},{"name":"CCTV-9高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv9hd","phone":"http://ivi.bupt.edu.cn/hls/cctv9hd.m3u8"},{"name":"CCTV-10高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv10hd","phone":"http://ivi.bupt.edu.cn/hls/cctv10hd.m3u8"},{"name":"CCTV-12高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv12hd","phone":"http://ivi.bupt.edu.cn/hls/cctv12hd.m3u8"},{"name":"CCTV-13高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv13hd","phone":"http://ivi.bupt.edu.cn/hls/cctv13hd.m3u8"},{"name":"CCTV-14高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv14hd","phone":"http://ivi.bupt.edu.cn/hls/cctv14hd.m3u8"},{"name":"CCTV-17高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv17hd","phone":"http://ivi.bupt.edu.cn/hls/cctv17hd.m3u8"},{"name":"CGTN高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cgtnhd","phone":"http://ivi.bupt.edu.cn/hls/cgtnhd.m3u8"},{"name":"CGTN DOC高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cgtndochd","phone":"http://ivi.bupt.edu.cn/hls/cgtndochd.m3u8"},{"name":"CHC高清电影","pc":"http://ivi.bupt.edu.cn/player.html?channel=chchd","phone":"http://ivi.bupt.edu.cn/hls/chchd.m3u8"},{"name":"北京卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv1hd","phone":"http://ivi.bupt.edu.cn/hls/btv1hd.m3u8"},{"name":"北京文艺高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv2hd","phone":"http://ivi.bupt.edu.cn/hls/btv2hd.m3u8"},{"name":"北京影视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv4hd","phone":"http://ivi.bupt.edu.cn/hls/btv4hd.m3u8"},{"name":"北京新闻高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv9hd","phone":"http://ivi.bupt.edu.cn/hls/btv9hd.m3u8"},{"name":"北京卡酷少儿高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv9hd","phone":"http://ivi.bupt.edu.cn/hls/btv9hd.m3u8"},{"name":"北京冬奥纪实高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv11hd","phone":"http://ivi.bupt.edu.cn/hls/btv11hd.m3u8"},{"name":"湖南卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=hunanhd","phone":"http://ivi.bupt.edu.cn/hls/hunanhd.m3u8"},{"name":"江苏卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=jshd","phone":"http://ivi.bupt.edu.cn/hls/jshd.m3u8"},{"name":"东方卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=dfhd","phone":"http://ivi.bupt.edu.cn/hls/dfhd.m3u8"},{"name":"安徽卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=ahhd","phone":"http://ivi.bupt.edu.cn/hls/ahhd.m3u8"},{"name":"黑龙江卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=hljhd","phone":"http://ivi.bupt.edu.cn/hls/hljhd.m3u8"},{"name":"辽宁卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=lnhd","phone":"http://ivi.bupt.edu.cn/hls/lnhd.m3u8"},{"name":"深圳卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=szhd","phone":"http://ivi.bupt.edu.cn/hls/szhd.m3u8"},{"name":"广东卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=gdhd","phone":"http://ivi.bupt.edu.cn/hls/gdhd.m3u8"},{"name":"天津卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=tjhd","phone":"http://ivi.bupt.edu.cn/hls/tjhd.m3u8"},{"name":"湖北卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=hbhd","phone":"http://ivi.bupt.edu.cn/hls/hbhd.m3u8"},{"name":"山东卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=sdhd","phone":"http://ivi.bupt.edu.cn/hls/sdhd.m3u8"},{"name":"重庆卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cqhd","phone":"http://ivi.bupt.edu.cn/hls/cqhd.m3u8"},{"name":"上海纪实高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=docuchina","phone":"http://ivi.bupt.edu.cn/hls/docuchina.m3u8"},{"name":"金鹰纪实高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=gedocu","phone":"http://ivi.bupt.edu.cn/hls/gedocu.m3u8"},{"name":"福建东南卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=dnhd","phone":"http://ivi.bupt.edu.cn/hls/dnhd.m3u8"},{"name":"四川卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=schd","phone":"http://ivi.bupt.edu.cn/hls/schd.m3u8"},{"name":"河北卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=hebhd","phone":"http://ivi.bupt.edu.cn/hls/hebhd.m3u8"},{"name":"江西卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=jxhd","phone":"http://ivi.bupt.edu.cn/hls/jxhd.m3u8"},{"name":"河南卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=hnhd","phone":"http://ivi.bupt.edu.cn/hls/hnhd.m3u8"},{"name":"广西卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=gxhd","phone":"http://ivi.bupt.edu.cn/hls/gxhd.m3u8"},{"name":"吉林卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=jlhd","phone":"http://ivi.bupt.edu.cn/hls/jlhd.m3u8"},{"name":"CETV-1高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=cetv1hd","phone":"http://ivi.bupt.edu.cn/hls/cetv1hd.m3u8"},{"name":"海南卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=lyhd","phone":"http://ivi.bupt.edu.cn/hls/lyhd.m3u8"},{"name":"贵州卫视高清","pc":"http://ivi.bupt.edu.cn/player.html?channel=gzhd","phone":"http://ivi.bupt.edu.cn/hls/gzhd.m3u8"},{"name":"CCTV-1综合","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv1","phone":"http://ivi.bupt.edu.cn/hls/cctv1.m3u8"},{"name":"CCTV-2财经","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv2","phone":"http://ivi.bupt.edu.cn/hls/cctv2.m3u8"},{"name":"CCTV-3综艺","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv3","phone":"http://ivi.bupt.edu.cn/hls/cctv3.m3u8"},{"name":"CCTV-4中文国际","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv4","phone":"http://ivi.bupt.edu.cn/hls/cctv4.m3u8"},{"name":"CCTV-6电影","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv6","phone":"http://ivi.bupt.edu.cn/hls/cctv6.m3u8"},{"name":"CCTV-7国防军事","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv7","phone":"http://ivi.bupt.edu.cn/hls/cctv7.m3u8"},{"name":"CCTV-8电视剧","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv8","phone":"http://ivi.bupt.edu.cn/hls/cctv8.m3u8"},{"name":"CCTV-9纪录","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv9","phone":"http://ivi.bupt.edu.cn/hls/cctv9.m3u8"},{"name":"CCTV-10科教","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv10","phone":"http://ivi.bupt.edu.cn/hls/cctv10.m3u8"},{"name":"CCTV-11戏曲","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv11","phone":"http://ivi.bupt.edu.cn/hls/cctv11.m3u8"},{"name":"CCTV-12社会与法","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv12","phone":"http://ivi.bupt.edu.cn/hls/cctv12.m3u8"},{"name":"CCTV-13新闻","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv13","phone":"http://ivi.bupt.edu.cn/hls/cctv13.m3u8"},{"name":"CCTV-14少儿","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv14","phone":"http://ivi.bupt.edu.cn/hls/cctv14.m3u8"},{"name":"CCTV-15音乐","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv15","phone":"http://ivi.bupt.edu.cn/hls/cctv15.m3u8"},{"name":"CGTN","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv16","phone":"http://ivi.bupt.edu.cn/hls/cctv16.m3u8"},{"name":"CCTV-17农业农村","pc":"http://ivi.bupt.edu.cn/player.html?channel=cctv17","phone":"http://ivi.bupt.edu.cn/hls/cctv17.m3u8"},{"name":"北京卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv1","phone":"http://ivi.bupt.edu.cn/hls/btv1.m3u8"},{"name":"北京文艺","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv2","phone":"http://ivi.bupt.edu.cn/hls/btv2.m3u8"},{"name":"北京科教","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv3","phone":"http://ivi.bupt.edu.cn/hls/btv3.m3u8"},{"name":"北京影视","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv4","phone":"http://ivi.bupt.edu.cn/hls/btv4.m3u8"},{"name":"北京财经","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv5","phone":"http://ivi.bupt.edu.cn/hls/btv5.m3u8"},{"name":"北京生活","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv7","phone":"http://ivi.bupt.edu.cn/hls/btv7.m3u8"},{"name":"北京青年","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv8","phone":"http://ivi.bupt.edu.cn/hls/btv8.m3u8"},{"name":"北京新闻","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv9","phone":"http://ivi.bupt.edu.cn/hls/btv9.m3u8"},{"name":"北京卡酷少儿","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv10","phone":"http://ivi.bupt.edu.cn/hls/btv10.m3u8"},{"name":"北京冬奥纪实","pc":"http://ivi.bupt.edu.cn/player.html?channel=btv11","phone":"http://ivi.bupt.edu.cn/hls/btv11.m3u8"},{"name":"湖南卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=hunantv","phone":"http://ivi.bupt.edu.cn/hls/hunantv.m3u8"},{"name":"江苏卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=jstv","phone":"http://ivi.bupt.edu.cn/hls/jstv.m3u8"},{"name":"东方卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=dftv","phone":"http://ivi.bupt.edu.cn/hls/dftv.m3u8"},{"name":"深圳卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=sztv","phone":"http://ivi.bupt.edu.cn/hls/sztv.m3u8"},{"name":"安徽卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=ahtv","phone":"http://ivi.bupt.edu.cn/hls/ahtv.m3u8"},{"name":"河南卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=hntv","phone":"http://ivi.bupt.edu.cn/hls/hntv.m3u8"},{"name":"陕西卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=sxtv","phone":"http://ivi.bupt.edu.cn/hls/sxtv.m3u8"},{"name":"吉林卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=jltv","phone":"http://ivi.bupt.edu.cn/hls/jltv.m3u8"},{"name":"广东卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=gdtv","phone":"http://ivi.bupt.edu.cn/hls/gdtv.m3u8"},{"name":"山东卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=sdtv","phone":"http://ivi.bupt.edu.cn/hls/sdtv.m3u8"},{"name":"湖北卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=hbtv","phone":"http://ivi.bupt.edu.cn/hls/hbtv.m3u8"},{"name":"广西卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=gxtv","phone":"http://ivi.bupt.edu.cn/hls/gxtv.m3u8"},{"name":"河北卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=hebtv","phone":"http://ivi.bupt.edu.cn/hls/hebtv.m3u8"},{"name":"西藏卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=xztv","phone":"http://ivi.bupt.edu.cn/hls/xztv.m3u8"},{"name":"内蒙古卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=nmtv","phone":"http://ivi.bupt.edu.cn/hls/nmtv.m3u8"},{"name":"青海卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=qhtv","phone":"http://ivi.bupt.edu.cn/hls/qhtv.m3u8"},{"name":"四川卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=sctv","phone":"http://ivi.bupt.edu.cn/hls/sctv.m3u8"},{"name":"天津卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=tjtv","phone":"http://ivi.bupt.edu.cn/hls/tjtv.m3u8"},{"name":"山西卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=sxrtv","phone":"http://ivi.bupt.edu.cn/hls/sxrtv.m3u8"},{"name":"辽宁卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=lntv","phone":"http://ivi.bupt.edu.cn/hls/lntv.m3u8"},{"name":"厦门卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=xmtv","phone":"http://ivi.bupt.edu.cn/hls/xmtv.m3u8"},{"name":"新疆卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=xjtv","phone":"http://ivi.bupt.edu.cn/hls/xjtv.m3u8"},{"name":"黑龙江卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=hljtv","phone":"http://ivi.bupt.edu.cn/hls/hljtv.m3u8"},{"name":"云南卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=yntv","phone":"http://ivi.bupt.edu.cn/hls/yntv.m3u8"},{"name":"江西卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=jxtv","phone":"http://ivi.bupt.edu.cn/hls/jxtv.m3u8"},{"name":"福建东南卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=dntv","phone":"http://ivi.bupt.edu.cn/hls/dntv.m3u8"},{"name":"贵州卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=gztv","phone":"http://ivi.bupt.edu.cn/hls/gztv.m3u8"},{"name":"宁夏卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=nxtv","phone":"http://ivi.bupt.edu.cn/hls/nxtv.m3u8"},{"name":"甘肃卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=gstv","phone":"http://ivi.bupt.edu.cn/hls/gstv.m3u8"},{"name":"重庆卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=cqtv","phone":"http://ivi.bupt.edu.cn/hls/cqtv.m3u8"},{"name":"兵团卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=bttv","phone":"http://ivi.bupt.edu.cn/hls/bttv.m3u8"},{"name":"延边卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=ybtv","phone":"http://ivi.bupt.edu.cn/hls/ybtv.m3u8"},{"name":"三沙卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=sstv","phone":"http://ivi.bupt.edu.cn/hls/sstv.m3u8"},{"name":"海南卫视","pc":"http://ivi.bupt.edu.cn/player.html?channel=lytv","phone":"http://ivi.bupt.edu.cn/hls/lytv.m3u8"},{"name":"CETV-1","pc":"http://ivi.bupt.edu.cn/player.html?channel=cetv1","phone":"http://ivi.bupt.edu.cn/hls/cetv1.m3u8"},{"name":"CETV-3","pc":"http://ivi.bupt.edu.cn/player.html?channel=cetv3","phone":"http://ivi.bupt.edu.cn/hls/cetv3.m3u8"},{"name":"CETV-4","pc":"http://ivi.bupt.edu.cn/player.html?channel=cetv4","phone":"http://ivi.bupt.edu.cn/hls/cetv4.m3u8"},{"name":"山东教育","pc":"http://ivi.bupt.edu.cn/player.html?channel=sdetv","phone":"http://ivi.bupt.edu.cn/hls/sdetv.m3u8"}]}

    @Test
    public void test_playerDatas() {
        String url = "http://ivi.bupt.edu.cn";
        StringBuffer json = new StringBuffer("{\"data\":[");
//        {"name":"","pc":"","phone":""},
        try {
            Document document = Jsoup.connect(url).get();
//            System.out.println("zcw_player:" + document.text());
            Elements elements = document.select("div .row div");
            for (Element element : elements) {
//                System.out.println("====blok===");
//                System.out.println(
//                        element
//
//                );
//                System.out.println("====blok===end");

                Element pEle = element.selectFirst("div p");
                if (pEle != null) {
                    System.out.println("zcw_player:<p>---" + pEle.wholeText());
                    String key = pEle.wholeText();
                    Elements aEles = element.select("a");

                    if (aEles.first() != null) {
                        String first = url + aEles.first().attr("href");
                        String last = url + aEles.last().attr("href");

                        System.out.println("zcw_player:<a>--first--->" + first);
                        System.out.println("zcw_player:<a>--last--->" + last);

                        json.append("{\"name\":");
                        json.append("\"" + key + "\",");
                        json.append("\"pc\":");
                        json.append("\"" + first + "\",");
                        json.append("\"phone\":");
                        json.append("\"" + last + "\"},");
                    }


                }
            }

            if (json.toString().endsWith(",")) {

                String result = json.subSequence(0, json.toString().length() - 1) + "]}";
                System.out.println(result);

            } else {

                json.append("]}");
                System.out.println(json.toString());
            }


        } catch (
                IOException e) {
            e.printStackTrace();
        }

    }
}