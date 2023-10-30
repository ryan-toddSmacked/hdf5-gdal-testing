


#include <gdal_priv.h>
#include <cstdio>
#include <cstdint>

#define ROWS 16
#define COLS 16


static const uint8_t turku[256][3] = {
    {(uint8_t)(255 * 0.000063), (uint8_t)(255 * 0.000005), (uint8_t)(255 * 0.000036)},
    {(uint8_t)(255 * 0.007290), (uint8_t)(255 * 0.007204), (uint8_t)(255 * 0.006548)},
    {(uint8_t)(255 * 0.014710), (uint8_t)(255 * 0.014597), (uint8_t)(255 * 0.013245)},
    {(uint8_t)(255 * 0.021935), (uint8_t)(255 * 0.021794), (uint8_t)(255 * 0.019755)},
    {(uint8_t)(255 * 0.029159), (uint8_t)(255 * 0.028991), (uint8_t)(255 * 0.026252)},
    {(uint8_t)(255 * 0.036570), (uint8_t)(255 * 0.036375), (uint8_t)(255 * 0.032748)},
    {(uint8_t)(255 * 0.043586), (uint8_t)(255 * 0.043359), (uint8_t)(255 * 0.039417)},
    {(uint8_t)(255 * 0.050168), (uint8_t)(255 * 0.049959), (uint8_t)(255 * 0.045556)},
    {(uint8_t)(255 * 0.056203), (uint8_t)(255 * 0.055961), (uint8_t)(255 * 0.051274)},
    {(uint8_t)(255 * 0.061712), (uint8_t)(255 * 0.061463), (uint8_t)(255 * 0.056643)},
    {(uint8_t)(255 * 0.066992), (uint8_t)(255 * 0.066746), (uint8_t)(255 * 0.061506)},
    {(uint8_t)(255 * 0.071921), (uint8_t)(255 * 0.071694), (uint8_t)(255 * 0.066226)},
    {(uint8_t)(255 * 0.076552), (uint8_t)(255 * 0.076296), (uint8_t)(255 * 0.070642)},
    {(uint8_t)(255 * 0.081056), (uint8_t)(255 * 0.080777), (uint8_t)(255 * 0.074828)},
    {(uint8_t)(255 * 0.085276), (uint8_t)(255 * 0.085021), (uint8_t)(255 * 0.078791)},
    {(uint8_t)(255 * 0.089398), (uint8_t)(255 * 0.089110), (uint8_t)(255 * 0.082660)},
    {(uint8_t)(255 * 0.093274), (uint8_t)(255 * 0.092973), (uint8_t)(255 * 0.086288)},
    {(uint8_t)(255 * 0.097120), (uint8_t)(255 * 0.096859), (uint8_t)(255 * 0.089825)},
    {(uint8_t)(255 * 0.101038), (uint8_t)(255 * 0.100786), (uint8_t)(255 * 0.093141)},
    {(uint8_t)(255 * 0.104942), (uint8_t)(255 * 0.104672), (uint8_t)(255 * 0.096482)},
    {(uint8_t)(255 * 0.108926), (uint8_t)(255 * 0.108623), (uint8_t)(255 * 0.099864)},
    {(uint8_t)(255 * 0.112921), (uint8_t)(255 * 0.112617), (uint8_t)(255 * 0.103237)},
    {(uint8_t)(255 * 0.116855), (uint8_t)(255 * 0.116562), (uint8_t)(255 * 0.106586)},
    {(uint8_t)(255 * 0.120820), (uint8_t)(255 * 0.120496), (uint8_t)(255 * 0.109910)},
    {(uint8_t)(255 * 0.124835), (uint8_t)(255 * 0.124484), (uint8_t)(255 * 0.113213)},
    {(uint8_t)(255 * 0.128844), (uint8_t)(255 * 0.128498), (uint8_t)(255 * 0.116492)},
    {(uint8_t)(255 * 0.132892), (uint8_t)(255 * 0.132513), (uint8_t)(255 * 0.119746)},
    {(uint8_t)(255 * 0.136918), (uint8_t)(255 * 0.136502), (uint8_t)(255 * 0.122995)},
    {(uint8_t)(255 * 0.140991), (uint8_t)(255 * 0.140564), (uint8_t)(255 * 0.126296)},
    {(uint8_t)(255 * 0.145046), (uint8_t)(255 * 0.144601), (uint8_t)(255 * 0.129527)},
    {(uint8_t)(255 * 0.149082), (uint8_t)(255 * 0.148613), (uint8_t)(255 * 0.132748)},
    {(uint8_t)(255 * 0.153138), (uint8_t)(255 * 0.152668), (uint8_t)(255 * 0.135908)},
    {(uint8_t)(255 * 0.157222), (uint8_t)(255 * 0.156756), (uint8_t)(255 * 0.139098)},
    {(uint8_t)(255 * 0.161345), (uint8_t)(255 * 0.160812), (uint8_t)(255 * 0.142280)},
    {(uint8_t)(255 * 0.165385), (uint8_t)(255 * 0.164875), (uint8_t)(255 * 0.145443)},
    {(uint8_t)(255 * 0.169533), (uint8_t)(255 * 0.168986), (uint8_t)(255 * 0.148500)},
    {(uint8_t)(255 * 0.173607), (uint8_t)(255 * 0.173041), (uint8_t)(255 * 0.151594)},
    {(uint8_t)(255 * 0.177744), (uint8_t)(255 * 0.177142), (uint8_t)(255 * 0.154657)},
    {(uint8_t)(255 * 0.181809), (uint8_t)(255 * 0.181208), (uint8_t)(255 * 0.157690)},
    {(uint8_t)(255 * 0.185960), (uint8_t)(255 * 0.185342), (uint8_t)(255 * 0.160696)},
    {(uint8_t)(255 * 0.190051), (uint8_t)(255 * 0.189414), (uint8_t)(255 * 0.163707)},
    {(uint8_t)(255 * 0.194194), (uint8_t)(255 * 0.193519), (uint8_t)(255 * 0.166642)},
    {(uint8_t)(255 * 0.198278), (uint8_t)(255 * 0.197608), (uint8_t)(255 * 0.169573)},
    {(uint8_t)(255 * 0.202395), (uint8_t)(255 * 0.201692), (uint8_t)(255 * 0.172431)},
    {(uint8_t)(255 * 0.206547), (uint8_t)(255 * 0.205817), (uint8_t)(255 * 0.175300)},
    {(uint8_t)(255 * 0.210638), (uint8_t)(255 * 0.209903), (uint8_t)(255 * 0.178153)},
    {(uint8_t)(255 * 0.214745), (uint8_t)(255 * 0.214009), (uint8_t)(255 * 0.180907)},
    {(uint8_t)(255 * 0.218872), (uint8_t)(255 * 0.218103), (uint8_t)(255 * 0.183680)},
    {(uint8_t)(255 * 0.222990), (uint8_t)(255 * 0.222187), (uint8_t)(255 * 0.186423)},
    {(uint8_t)(255 * 0.227091), (uint8_t)(255 * 0.226298), (uint8_t)(255 * 0.189124)},
    {(uint8_t)(255 * 0.231200), (uint8_t)(255 * 0.230358), (uint8_t)(255 * 0.191783)},
    {(uint8_t)(255 * 0.235309), (uint8_t)(255 * 0.234470), (uint8_t)(255 * 0.194450)},
    {(uint8_t)(255 * 0.239393), (uint8_t)(255 * 0.238528), (uint8_t)(255 * 0.197043)},
    {(uint8_t)(255 * 0.243470), (uint8_t)(255 * 0.242609), (uint8_t)(255 * 0.199581)},
    {(uint8_t)(255 * 0.247581), (uint8_t)(255 * 0.246687), (uint8_t)(255 * 0.202127)},
    {(uint8_t)(255 * 0.251671), (uint8_t)(255 * 0.250761), (uint8_t)(255 * 0.204658)},
    {(uint8_t)(255 * 0.255736), (uint8_t)(255 * 0.254845), (uint8_t)(255 * 0.207134)},
    {(uint8_t)(255 * 0.259822), (uint8_t)(255 * 0.258900), (uint8_t)(255 * 0.209562)},
    {(uint8_t)(255 * 0.263900), (uint8_t)(255 * 0.262954), (uint8_t)(255 * 0.211994)},
    {(uint8_t)(255 * 0.267938), (uint8_t)(255 * 0.266992), (uint8_t)(255 * 0.214362)},
    {(uint8_t)(255 * 0.271997), (uint8_t)(255 * 0.271056), (uint8_t)(255 * 0.216724)},
    {(uint8_t)(255 * 0.276087), (uint8_t)(255 * 0.275096), (uint8_t)(255 * 0.219036)},
    {(uint8_t)(255 * 0.280118), (uint8_t)(255 * 0.279144), (uint8_t)(255 * 0.221330)},
    {(uint8_t)(255 * 0.284164), (uint8_t)(255 * 0.283175), (uint8_t)(255 * 0.223587)},
    {(uint8_t)(255 * 0.288207), (uint8_t)(255 * 0.287188), (uint8_t)(255 * 0.225833)},
    {(uint8_t)(255 * 0.292251), (uint8_t)(255 * 0.291232), (uint8_t)(255 * 0.228039)},
    {(uint8_t)(255 * 0.296286), (uint8_t)(255 * 0.295240), (uint8_t)(255 * 0.230190)},
    {(uint8_t)(255 * 0.300312), (uint8_t)(255 * 0.299273), (uint8_t)(255 * 0.232366)},
    {(uint8_t)(255 * 0.304341), (uint8_t)(255 * 0.303270), (uint8_t)(255 * 0.234504)},
    {(uint8_t)(255 * 0.308370), (uint8_t)(255 * 0.307283), (uint8_t)(255 * 0.236608)},
    {(uint8_t)(255 * 0.312378), (uint8_t)(255 * 0.311297), (uint8_t)(255 * 0.238663)},
    {(uint8_t)(255 * 0.316418), (uint8_t)(255 * 0.315302), (uint8_t)(255 * 0.240716)},
    {(uint8_t)(255 * 0.320441), (uint8_t)(255 * 0.319304), (uint8_t)(255 * 0.242756)},
    {(uint8_t)(255 * 0.324438), (uint8_t)(255 * 0.323304), (uint8_t)(255 * 0.244764)},
    {(uint8_t)(255 * 0.328462), (uint8_t)(255 * 0.327290), (uint8_t)(255 * 0.246769)},
    {(uint8_t)(255 * 0.332488), (uint8_t)(255 * 0.331280), (uint8_t)(255 * 0.248761)},
    {(uint8_t)(255 * 0.336486), (uint8_t)(255 * 0.335297), (uint8_t)(255 * 0.250701)},
    {(uint8_t)(255 * 0.340511), (uint8_t)(255 * 0.339286), (uint8_t)(255 * 0.252648)},
    {(uint8_t)(255 * 0.344521), (uint8_t)(255 * 0.343272), (uint8_t)(255 * 0.254580)},
    {(uint8_t)(255 * 0.348549), (uint8_t)(255 * 0.347265), (uint8_t)(255 * 0.256467)},
    {(uint8_t)(255 * 0.352572), (uint8_t)(255 * 0.351248), (uint8_t)(255 * 0.258360)},
    {(uint8_t)(255 * 0.356605), (uint8_t)(255 * 0.355248), (uint8_t)(255 * 0.260248)},
    {(uint8_t)(255 * 0.360620), (uint8_t)(255 * 0.359220), (uint8_t)(255 * 0.262115)},
    {(uint8_t)(255 * 0.364666), (uint8_t)(255 * 0.363212), (uint8_t)(255 * 0.263983)},
    {(uint8_t)(255 * 0.368721), (uint8_t)(255 * 0.367205), (uint8_t)(255 * 0.265824)},
    {(uint8_t)(255 * 0.372762), (uint8_t)(255 * 0.371195), (uint8_t)(255 * 0.267635)},
    {(uint8_t)(255 * 0.376835), (uint8_t)(255 * 0.375195), (uint8_t)(255 * 0.269496)},
    {(uint8_t)(255 * 0.380907), (uint8_t)(255 * 0.379198), (uint8_t)(255 * 0.271303)},
    {(uint8_t)(255 * 0.384975), (uint8_t)(255 * 0.383208), (uint8_t)(255 * 0.273127)},
    {(uint8_t)(255 * 0.389080), (uint8_t)(255 * 0.387201), (uint8_t)(255 * 0.274933)},
    {(uint8_t)(255 * 0.393179), (uint8_t)(255 * 0.391225), (uint8_t)(255 * 0.276752)},
    {(uint8_t)(255 * 0.397300), (uint8_t)(255 * 0.395235), (uint8_t)(255 * 0.278557)},
    {(uint8_t)(255 * 0.401442), (uint8_t)(255 * 0.399243), (uint8_t)(255 * 0.280346)},
    {(uint8_t)(255 * 0.405602), (uint8_t)(255 * 0.403280), (uint8_t)(255 * 0.282175)},
    {(uint8_t)(255 * 0.409774), (uint8_t)(255 * 0.407305), (uint8_t)(255 * 0.283967)},
    {(uint8_t)(255 * 0.413963), (uint8_t)(255 * 0.411339), (uint8_t)(255 * 0.285769)},
    {(uint8_t)(255 * 0.418173), (uint8_t)(255 * 0.415382), (uint8_t)(255 * 0.287587)},
    {(uint8_t)(255 * 0.422409), (uint8_t)(255 * 0.419437), (uint8_t)(255 * 0.289423)},
    {(uint8_t)(255 * 0.426680), (uint8_t)(255 * 0.423481), (uint8_t)(255 * 0.291250)},
    {(uint8_t)(255 * 0.430975), (uint8_t)(255 * 0.427557), (uint8_t)(255 * 0.293070)},
    {(uint8_t)(255 * 0.435297), (uint8_t)(255 * 0.431630), (uint8_t)(255 * 0.294913)},
    {(uint8_t)(255 * 0.439639), (uint8_t)(255 * 0.435704), (uint8_t)(255 * 0.296782)},
    {(uint8_t)(255 * 0.444025), (uint8_t)(255 * 0.439786), (uint8_t)(255 * 0.298639)},
    {(uint8_t)(255 * 0.448436), (uint8_t)(255 * 0.443882), (uint8_t)(255 * 0.300514)},
    {(uint8_t)(255 * 0.452890), (uint8_t)(255 * 0.447974), (uint8_t)(255 * 0.302404)},
    {(uint8_t)(255 * 0.457371), (uint8_t)(255 * 0.452098), (uint8_t)(255 * 0.304323)},
    {(uint8_t)(255 * 0.461904), (uint8_t)(255 * 0.456207), (uint8_t)(255 * 0.306269)},
    {(uint8_t)(255 * 0.466474), (uint8_t)(255 * 0.460328), (uint8_t)(255 * 0.308200)},
    {(uint8_t)(255 * 0.471093), (uint8_t)(255 * 0.464479), (uint8_t)(255 * 0.310185)},
    {(uint8_t)(255 * 0.475755), (uint8_t)(255 * 0.468613), (uint8_t)(255 * 0.312149)},
    {(uint8_t)(255 * 0.480458), (uint8_t)(255 * 0.472760), (uint8_t)(255 * 0.314179)},
    {(uint8_t)(255 * 0.485214), (uint8_t)(255 * 0.476920), (uint8_t)(255 * 0.316230)},
    {(uint8_t)(255 * 0.490030), (uint8_t)(255 * 0.481079), (uint8_t)(255 * 0.318289)},
    {(uint8_t)(255 * 0.494902), (uint8_t)(255 * 0.485249), (uint8_t)(255 * 0.320397)},
    {(uint8_t)(255 * 0.499813), (uint8_t)(255 * 0.489423), (uint8_t)(255 * 0.322518)},
    {(uint8_t)(255 * 0.504804), (uint8_t)(255 * 0.493606), (uint8_t)(255 * 0.324659)},
    {(uint8_t)(255 * 0.509839), (uint8_t)(255 * 0.497800), (uint8_t)(255 * 0.326847)},
    {(uint8_t)(255 * 0.514941), (uint8_t)(255 * 0.501978), (uint8_t)(255 * 0.329089)},
    {(uint8_t)(255 * 0.520096), (uint8_t)(255 * 0.506153), (uint8_t)(255 * 0.331326)},
    {(uint8_t)(255 * 0.525329), (uint8_t)(255 * 0.510340), (uint8_t)(255 * 0.333638)},
    {(uint8_t)(255 * 0.530619), (uint8_t)(255 * 0.514527), (uint8_t)(255 * 0.335961)},
    {(uint8_t)(255 * 0.535971), (uint8_t)(255 * 0.518703), (uint8_t)(255 * 0.338327)},
    {(uint8_t)(255 * 0.541388), (uint8_t)(255 * 0.522867), (uint8_t)(255 * 0.340746)},
    {(uint8_t)(255 * 0.546882), (uint8_t)(255 * 0.527027), (uint8_t)(255 * 0.343200)},
    {(uint8_t)(255 * 0.552434), (uint8_t)(255 * 0.531166), (uint8_t)(255 * 0.345677)},
    {(uint8_t)(255 * 0.558042), (uint8_t)(255 * 0.535291), (uint8_t)(255 * 0.348217)},
    {(uint8_t)(255 * 0.563732), (uint8_t)(255 * 0.539401), (uint8_t)(255 * 0.350797)},
    {(uint8_t)(255 * 0.569463), (uint8_t)(255 * 0.543493), (uint8_t)(255 * 0.353400)},
    {(uint8_t)(255 * 0.575270), (uint8_t)(255 * 0.547552), (uint8_t)(255 * 0.356064)},
    {(uint8_t)(255 * 0.581129), (uint8_t)(255 * 0.551588), (uint8_t)(255 * 0.358745)},
    {(uint8_t)(255 * 0.587044), (uint8_t)(255 * 0.555576), (uint8_t)(255 * 0.361493)},
    {(uint8_t)(255 * 0.593020), (uint8_t)(255 * 0.559543), (uint8_t)(255 * 0.364264)},
    {(uint8_t)(255 * 0.599036), (uint8_t)(255 * 0.563464), (uint8_t)(255 * 0.367083)},
    {(uint8_t)(255 * 0.605096), (uint8_t)(255 * 0.567331), (uint8_t)(255 * 0.369934)},
    {(uint8_t)(255 * 0.611203), (uint8_t)(255 * 0.571142), (uint8_t)(255 * 0.372824)},
    {(uint8_t)(255 * 0.617339), (uint8_t)(255 * 0.574902), (uint8_t)(255 * 0.375753)},
    {(uint8_t)(255 * 0.623515), (uint8_t)(255 * 0.578604), (uint8_t)(255 * 0.378712)},
    {(uint8_t)(255 * 0.629702), (uint8_t)(255 * 0.582236), (uint8_t)(255 * 0.381703)},
    {(uint8_t)(255 * 0.635919), (uint8_t)(255 * 0.585808), (uint8_t)(255 * 0.384716)},
    {(uint8_t)(255 * 0.642146), (uint8_t)(255 * 0.589285), (uint8_t)(255 * 0.387761)},
    {(uint8_t)(255 * 0.648375), (uint8_t)(255 * 0.592706), (uint8_t)(255 * 0.390839)},
    {(uint8_t)(255 * 0.654606), (uint8_t)(255 * 0.596023), (uint8_t)(255 * 0.393922)},
    {(uint8_t)(255 * 0.660832), (uint8_t)(255 * 0.599263), (uint8_t)(255 * 0.397028)},
    {(uint8_t)(255 * 0.667046), (uint8_t)(255 * 0.602403), (uint8_t)(255 * 0.400161)},
    {(uint8_t)(255 * 0.673242), (uint8_t)(255 * 0.605450), (uint8_t)(255 * 0.403304)},
    {(uint8_t)(255 * 0.679400), (uint8_t)(255 * 0.608411), (uint8_t)(255 * 0.406452)},
    {(uint8_t)(255 * 0.685537), (uint8_t)(255 * 0.611258), (uint8_t)(255 * 0.409610)},
    {(uint8_t)(255 * 0.691626), (uint8_t)(255 * 0.613996), (uint8_t)(255 * 0.412779)},
    {(uint8_t)(255 * 0.697668), (uint8_t)(255 * 0.616646), (uint8_t)(255 * 0.415935)},
    {(uint8_t)(255 * 0.703665), (uint8_t)(255 * 0.619184), (uint8_t)(255 * 0.419105)},
    {(uint8_t)(255 * 0.709603), (uint8_t)(255 * 0.621600), (uint8_t)(255 * 0.422261)},
    {(uint8_t)(255 * 0.715479), (uint8_t)(255 * 0.623928), (uint8_t)(255 * 0.425434)},
    {(uint8_t)(255 * 0.721279), (uint8_t)(255 * 0.626132), (uint8_t)(255 * 0.428588)},
    {(uint8_t)(255 * 0.727018), (uint8_t)(255 * 0.628240), (uint8_t)(255 * 0.431748)},
    {(uint8_t)(255 * 0.732685), (uint8_t)(255 * 0.630234), (uint8_t)(255 * 0.434886)},
    {(uint8_t)(255 * 0.738264), (uint8_t)(255 * 0.632122), (uint8_t)(255 * 0.438021)},
    {(uint8_t)(255 * 0.743772), (uint8_t)(255 * 0.633913), (uint8_t)(255 * 0.441135)},
    {(uint8_t)(255 * 0.749190), (uint8_t)(255 * 0.635592), (uint8_t)(255 * 0.444261)},
    {(uint8_t)(255 * 0.754538), (uint8_t)(255 * 0.637182), (uint8_t)(255 * 0.447354)},
    {(uint8_t)(255 * 0.759785), (uint8_t)(255 * 0.638671), (uint8_t)(255 * 0.450458)},
    {(uint8_t)(255 * 0.764961), (uint8_t)(255 * 0.640074), (uint8_t)(255 * 0.453543)},
    {(uint8_t)(255 * 0.770042), (uint8_t)(255 * 0.641377), (uint8_t)(255 * 0.456625)},
    {(uint8_t)(255 * 0.775042), (uint8_t)(255 * 0.642610), (uint8_t)(255 * 0.459703)},
    {(uint8_t)(255 * 0.779960), (uint8_t)(255 * 0.643752), (uint8_t)(255 * 0.462766)},
    {(uint8_t)(255 * 0.784800), (uint8_t)(255 * 0.644824), (uint8_t)(255 * 0.465838)},
    {(uint8_t)(255 * 0.789553), (uint8_t)(255 * 0.645828), (uint8_t)(255 * 0.468920)},
    {(uint8_t)(255 * 0.794231), (uint8_t)(255 * 0.646771), (uint8_t)(255 * 0.471996)},
    {(uint8_t)(255 * 0.798829), (uint8_t)(255 * 0.647646), (uint8_t)(255 * 0.475078)},
    {(uint8_t)(255 * 0.803353), (uint8_t)(255 * 0.648471), (uint8_t)(255 * 0.478158)},
    {(uint8_t)(255 * 0.807810), (uint8_t)(255 * 0.649254), (uint8_t)(255 * 0.481257)},
    {(uint8_t)(255 * 0.812197), (uint8_t)(255 * 0.649987), (uint8_t)(255 * 0.484375)},
    {(uint8_t)(255 * 0.816524), (uint8_t)(255 * 0.650686), (uint8_t)(255 * 0.487527)},
    {(uint8_t)(255 * 0.820782), (uint8_t)(255 * 0.651357), (uint8_t)(255 * 0.490694)},
    {(uint8_t)(255 * 0.824986), (uint8_t)(255 * 0.652004), (uint8_t)(255 * 0.493880)},
    {(uint8_t)(255 * 0.829142), (uint8_t)(255 * 0.652627), (uint8_t)(255 * 0.497108)},
    {(uint8_t)(255 * 0.833237), (uint8_t)(255 * 0.653245), (uint8_t)(255 * 0.500370)},
    {(uint8_t)(255 * 0.837292), (uint8_t)(255 * 0.653864), (uint8_t)(255 * 0.503681)},
    {(uint8_t)(255 * 0.841297), (uint8_t)(255 * 0.654478), (uint8_t)(255 * 0.507039)},
    {(uint8_t)(255 * 0.845261), (uint8_t)(255 * 0.655103), (uint8_t)(255 * 0.510449)},
    {(uint8_t)(255 * 0.849192), (uint8_t)(255 * 0.655752), (uint8_t)(255 * 0.513925)},
    {(uint8_t)(255 * 0.853082), (uint8_t)(255 * 0.656418), (uint8_t)(255 * 0.517457)},
    {(uint8_t)(255 * 0.856942), (uint8_t)(255 * 0.657111), (uint8_t)(255 * 0.521050)},
    {(uint8_t)(255 * 0.860774), (uint8_t)(255 * 0.657841), (uint8_t)(255 * 0.524721)},
    {(uint8_t)(255 * 0.864578), (uint8_t)(255 * 0.658606), (uint8_t)(255 * 0.528473)},
    {(uint8_t)(255 * 0.868361), (uint8_t)(255 * 0.659428), (uint8_t)(255 * 0.532304)},
    {(uint8_t)(255 * 0.872114), (uint8_t)(255 * 0.660303), (uint8_t)(255 * 0.536217)},
    {(uint8_t)(255 * 0.875845), (uint8_t)(255 * 0.661242), (uint8_t)(255 * 0.540221)},
    {(uint8_t)(255 * 0.879553), (uint8_t)(255 * 0.662254), (uint8_t)(255 * 0.544323)},
    {(uint8_t)(255 * 0.883246), (uint8_t)(255 * 0.663333), (uint8_t)(255 * 0.548526)},
    {(uint8_t)(255 * 0.886919), (uint8_t)(255 * 0.664485), (uint8_t)(255 * 0.552814)},
    {(uint8_t)(255 * 0.890568), (uint8_t)(255 * 0.665734), (uint8_t)(255 * 0.557222)},
    {(uint8_t)(255 * 0.894201), (uint8_t)(255 * 0.667068), (uint8_t)(255 * 0.561722)},
    {(uint8_t)(255 * 0.897809), (uint8_t)(255 * 0.668505), (uint8_t)(255 * 0.566329)},
    {(uint8_t)(255 * 0.901394), (uint8_t)(255 * 0.670040), (uint8_t)(255 * 0.571039)},
    {(uint8_t)(255 * 0.904958), (uint8_t)(255 * 0.671670), (uint8_t)(255 * 0.575872)},
    {(uint8_t)(255 * 0.908492), (uint8_t)(255 * 0.673419), (uint8_t)(255 * 0.580791)},
    {(uint8_t)(255 * 0.911997), (uint8_t)(255 * 0.675275), (uint8_t)(255 * 0.585829)},
    {(uint8_t)(255 * 0.915467), (uint8_t)(255 * 0.677253), (uint8_t)(255 * 0.590958)},
    {(uint8_t)(255 * 0.918906), (uint8_t)(255 * 0.679333), (uint8_t)(255 * 0.596195)},
    {(uint8_t)(255 * 0.922312), (uint8_t)(255 * 0.681539), (uint8_t)(255 * 0.601525)},
    {(uint8_t)(255 * 0.925669), (uint8_t)(255 * 0.683866), (uint8_t)(255 * 0.606956)},
    {(uint8_t)(255 * 0.928977), (uint8_t)(255 * 0.686316), (uint8_t)(255 * 0.612460)},
    {(uint8_t)(255 * 0.932238), (uint8_t)(255 * 0.688886), (uint8_t)(255 * 0.618058)},
    {(uint8_t)(255 * 0.935448), (uint8_t)(255 * 0.691564), (uint8_t)(255 * 0.623735)},
    {(uint8_t)(255 * 0.938597), (uint8_t)(255 * 0.694360), (uint8_t)(255 * 0.629468)},
    {(uint8_t)(255 * 0.941681), (uint8_t)(255 * 0.697278), (uint8_t)(255 * 0.635273)},
    {(uint8_t)(255 * 0.944702), (uint8_t)(255 * 0.700307), (uint8_t)(255 * 0.641130)},
    {(uint8_t)(255 * 0.947647), (uint8_t)(255 * 0.703444), (uint8_t)(255 * 0.647044)},
    {(uint8_t)(255 * 0.950518), (uint8_t)(255 * 0.706687), (uint8_t)(255 * 0.652983)},
    {(uint8_t)(255 * 0.953313), (uint8_t)(255 * 0.710026), (uint8_t)(255 * 0.658964)},
    {(uint8_t)(255 * 0.956025), (uint8_t)(255 * 0.713462), (uint8_t)(255 * 0.664967)},
    {(uint8_t)(255 * 0.958650), (uint8_t)(255 * 0.716995), (uint8_t)(255 * 0.670991)},
    {(uint8_t)(255 * 0.961187), (uint8_t)(255 * 0.720602), (uint8_t)(255 * 0.677020)},
    {(uint8_t)(255 * 0.963634), (uint8_t)(255 * 0.724299), (uint8_t)(255 * 0.683043)},
    {(uint8_t)(255 * 0.965991), (uint8_t)(255 * 0.728067), (uint8_t)(255 * 0.689068)},
    {(uint8_t)(255 * 0.968259), (uint8_t)(255 * 0.731909), (uint8_t)(255 * 0.695067)},
    {(uint8_t)(255 * 0.970426), (uint8_t)(255 * 0.735806), (uint8_t)(255 * 0.701054)},
    {(uint8_t)(255 * 0.972506), (uint8_t)(255 * 0.739776), (uint8_t)(255 * 0.707015)},
    {(uint8_t)(255 * 0.974483), (uint8_t)(255 * 0.743783), (uint8_t)(255 * 0.712936)},
    {(uint8_t)(255 * 0.976371), (uint8_t)(255 * 0.747846), (uint8_t)(255 * 0.718828)},
    {(uint8_t)(255 * 0.978164), (uint8_t)(255 * 0.751946), (uint8_t)(255 * 0.724680)},
    {(uint8_t)(255 * 0.979870), (uint8_t)(255 * 0.756084), (uint8_t)(255 * 0.730482)},
    {(uint8_t)(255 * 0.981480), (uint8_t)(255 * 0.760255), (uint8_t)(255 * 0.736231)},
    {(uint8_t)(255 * 0.983000), (uint8_t)(255 * 0.764455), (uint8_t)(255 * 0.741938)},
    {(uint8_t)(255 * 0.984437), (uint8_t)(255 * 0.768675), (uint8_t)(255 * 0.747593)},
    {(uint8_t)(255 * 0.985784), (uint8_t)(255 * 0.772921), (uint8_t)(255 * 0.753181)},
    {(uint8_t)(255 * 0.987052), (uint8_t)(255 * 0.777189), (uint8_t)(255 * 0.758725)},
    {(uint8_t)(255 * 0.988234), (uint8_t)(255 * 0.781462), (uint8_t)(255 * 0.764206)},
    {(uint8_t)(255 * 0.989346), (uint8_t)(255 * 0.785749), (uint8_t)(255 * 0.769631)},
    {(uint8_t)(255 * 0.990378), (uint8_t)(255 * 0.790041), (uint8_t)(255 * 0.775001)},
    {(uint8_t)(255 * 0.991341), (uint8_t)(255 * 0.794346), (uint8_t)(255 * 0.780317)},
    {(uint8_t)(255 * 0.992236), (uint8_t)(255 * 0.798651), (uint8_t)(255 * 0.785580)},
    {(uint8_t)(255 * 0.993066), (uint8_t)(255 * 0.802958), (uint8_t)(255 * 0.790784)},
    {(uint8_t)(255 * 0.993829), (uint8_t)(255 * 0.807273), (uint8_t)(255 * 0.795937)},
    {(uint8_t)(255 * 0.994533), (uint8_t)(255 * 0.811585), (uint8_t)(255 * 0.801043)},
    {(uint8_t)(255 * 0.995180), (uint8_t)(255 * 0.815897), (uint8_t)(255 * 0.806101)},
    {(uint8_t)(255 * 0.995775), (uint8_t)(255 * 0.820203), (uint8_t)(255 * 0.811110)},
    {(uint8_t)(255 * 0.996319), (uint8_t)(255 * 0.824512), (uint8_t)(255 * 0.816079)},
    {(uint8_t)(255 * 0.996814), (uint8_t)(255 * 0.828824), (uint8_t)(255 * 0.821000)},
    {(uint8_t)(255 * 0.997265), (uint8_t)(255 * 0.833124), (uint8_t)(255 * 0.825884)},
    {(uint8_t)(255 * 0.997672), (uint8_t)(255 * 0.837430), (uint8_t)(255 * 0.830736)},
    {(uint8_t)(255 * 0.998039), (uint8_t)(255 * 0.841727), (uint8_t)(255 * 0.835548)},
    {(uint8_t)(255 * 0.998368), (uint8_t)(255 * 0.846020), (uint8_t)(255 * 0.840333)},
    {(uint8_t)(255 * 0.998661), (uint8_t)(255 * 0.850316), (uint8_t)(255 * 0.845083)},
    {(uint8_t)(255 * 0.998919), (uint8_t)(255 * 0.854608), (uint8_t)(255 * 0.849810)},
    {(uint8_t)(255 * 0.999146), (uint8_t)(255 * 0.858895), (uint8_t)(255 * 0.854509)},
    {(uint8_t)(255 * 0.999342), (uint8_t)(255 * 0.863188), (uint8_t)(255 * 0.859187)},
    {(uint8_t)(255 * 0.999510), (uint8_t)(255 * 0.867470), (uint8_t)(255 * 0.863851)},
    {(uint8_t)(255 * 0.999652), (uint8_t)(255 * 0.871758), (uint8_t)(255 * 0.868494)},
    {(uint8_t)(255 * 0.999769), (uint8_t)(255 * 0.876039), (uint8_t)(255 * 0.873116)},
    {(uint8_t)(255 * 0.999864), (uint8_t)(255 * 0.880320), (uint8_t)(255 * 0.877730)},
    {(uint8_t)(255 * 0.999937), (uint8_t)(255 * 0.884606), (uint8_t)(255 * 0.882330)},
    {(uint8_t)(255 * 0.999989), (uint8_t)(255 * 0.888890), (uint8_t)(255 * 0.886927)},
    {(uint8_t)(255 * 1.000000), (uint8_t)(255 * 0.893169), (uint8_t)(255 * 0.891512)},
    {(uint8_t)(255 * 1.000000), (uint8_t)(255 * 0.897457), (uint8_t)(255 * 0.896094)},
    {(uint8_t)(255 * 1.000000), (uint8_t)(255 * 0.901739), (uint8_t)(255 * 0.900670)}
};

int main()
{



    uint8_t* image = new uint8_t[ROWS*COLS];
    for (int i = 0; i < ROWS*COLS; i++)
        image[i] = i % 256;

    for (int i = 0; i < ROWS*COLS; i++)
        image[i] = (image[i] == 0) ? (1) : (image[i]);


    GDAL_GCP gcp[4];

    gcp[0].dfGCPPixel = 0.5;
    gcp[0].dfGCPLine = 0.5;
    gcp[0].dfGCPX = 10.00;
    gcp[0].dfGCPY = 10.00;
    gcp[0].pszId = NULL;
    gcp[0].pszInfo = NULL;

    gcp[1].dfGCPPixel = COLS - 0.5;
    gcp[1].dfGCPLine = 0.5;
    gcp[1].dfGCPX = 10.00;
    gcp[1].dfGCPY =  9.98;
    gcp[1].pszId = NULL;
    gcp[1].pszInfo = NULL;

    gcp[2].dfGCPPixel = COLS - 0.5;
    gcp[2].dfGCPLine = ROWS - 0.5;
    gcp[2].dfGCPX =  9.98;
    gcp[2].dfGCPY =  9.98;
    gcp[2].pszId = NULL;
    gcp[2].pszInfo = NULL;

    gcp[3].dfGCPPixel = 0.5;
    gcp[3].dfGCPLine = ROWS - 0.5;
    gcp[3].dfGCPX =  9.98;
    gcp[3].dfGCPY = 10.00;
    gcp[3].pszId = NULL;
    gcp[3].pszInfo = NULL;

    double geotransform[6];

    // Conver the GCPs to a geotransform
    int res = GDALGCPsToGeoTransform(4, (const GDAL_GCP*)gcp, geotransform, 0);

    // Register the geotiff driver
    GDALAllRegister();

    // Create new geotiff image
    // Add the ground control points
    // Set the coordinate system to WGS84
    // Set the no data value to 0
    // Set the image size to 100x100
    // Set the image type to Byte, which is the C equivalent of uint8_t
    // Set the image to be written to "test.tif"

    GDALDriver* driver = GetGDALDriverManager()->GetDriverByName("GTiff");
    GDALDataset* dataset = (GDALDataset*) GDALCreate(
            driver,
            "test.tif",
            COLS,
            ROWS,
            1,
            GDT_Byte,
            NULL
    );


    // Write the image to the geotiff
    GDALRasterBand* band = dataset->GetRasterBand(1);
    CPLErr err;
    for (int i = 0; i < ROWS; i++)
    {
        //for (int j = 0; j < COLS; j++)
        //    buffer[j] = image[i*COLS + j];
        err = band->RasterIO(GF_Write, 0, i, COLS, 1, image + i*COLS, COLS, 1, GDT_Byte, 0, 0);
    }
    delete[] image;

    GDALSetProjection(dataset, "WGS84");

    GDALSetGeoTransform(dataset, geotransform);

    // Set no data value to 0
    band->SetNoDataValue(0);

    // Set the color table of the image to the static color table
    GDALColorTable* ct = new GDALColorTable(GPI_RGB);

    for (int i = 0; i < 256; i++)
    {
        GDALColorEntry entry;
        entry.c1 = (short)turku[i][0];
        entry.c2 = (short)turku[i][1];
        entry.c3 = (short)turku[i][2];
        entry.c4 = 255;
        ct->SetColorEntry(i, &entry);
    }

    band->SetColorTable(ct);

    // Set the TIFFTAG_XRESOLUTION Tag to 100
    // and the TIFFTAG_YRESOLUTION Tag to 100
    // Set the TIFFTAG_RESOLUTIONUNIT Tag to 3, cm per pixel
    dataset->GetRasterBand(1)->SetMetadataItem("TIFFTAG_XRESOLUTION", "100", NULL);
    dataset->GetRasterBand(1)->SetMetadataItem("TIFFTAG_YRESOLUTION", "100", NULL);
    dataset->GetRasterBand(1)->SetMetadataItem("TIFFTAG_RESOLUTIONUNIT", "3", NULL);

    GDALClose(dataset);
    
    return 0;
}


