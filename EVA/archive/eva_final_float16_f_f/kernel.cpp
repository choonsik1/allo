
//===------------------------------------------------------------*- C++ -*-===//
//
// Automatically generated file for High-level Synthesis (HLS).
//
//===----------------------------------------------------------------------===//
#include <algorithm>
#include <ap_axi_sdata.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>
#include <hls_vector.h>
#include <math.h>
#include <stdint.h>
using namespace std;
void node_0_0(
  hls::stream< ap_uint<26> >& v0,
  hls::stream< ap_uint<26> >& v1,
  hls::stream< ap_uint<26> >& v2,
  hls::stream< ap_uint<26> >& v3,
  hls::stream< ap_uint<17> >& v4,
  hls::stream< ap_uint<17> >& v5,
  hls::stream< ap_uint<17> >& v6,
  hls::stream< ap_uint<17> >& v7,
  hls::stream< int32_t >& v8,
  hls::stream< int32_t >& v9,
  hls::stream< int32_t >& v10,
  hls::stream< int32_t >& v11,
  hls::stream< ap_uint<26> >& v12,
  hls::stream< ap_uint<26> >& v13,
  hls::stream< ap_uint<26> >& v14,
  hls::stream< ap_uint<26> >& v15,
  hls::stream< int32_t >& v16,
  hls::stream< int32_t >& v17,
  hls::stream< int32_t >& v18,
  hls::stream< int32_t >& v19,
  hls::stream< ap_uint<17> >& v20,
  hls::stream< ap_uint<17> >& v21,
  hls::stream< ap_uint<17> >& v22,
  hls::stream< ap_uint<17> >& v23
) {	// L2
  int32_t irf[8];	// L33
  for (int v25 = 0; v25 < 8; v25++) {	// L34
    irf[v25] = 0;	// L34
  }
  half drf[8];	// L35
  for (int v27 = 0; v27 < 8; v27++) {	// L36
    drf[v27] = (double)0.000000;	// L36
  }
  int32_t drf_full[8];	// L37
  for (int v29 = 0; v29 < 8; v29++) {	// L38
    drf_full[v29] = 0;	// L38
  }
  int32_t dsmask;	// L39
  dsmask = 0;	// L40
  int32_t crv_vld;	// L41
  crv_vld = 0;	// L42
  half crv_data;	// L43
  crv_data = (double)0.000000;	// L44
  int32_t crv_addr;	// L45
  crv_addr = 0;	// L46
  int32_t crv_mode;	// L47
  crv_mode = 0;	// L48
  int32_t crv_raw;	// L49
  crv_raw = 0;	// L50
  int32_t csd_vld;	// L51
  csd_vld = 0;	// L52
  ap_uint<26> csd_pkt;	// L53
  csd_pkt = 0;	// L54
  int32_t csd_dir;	// L55
  csd_dir = 0;	// L56
  int32_t row_id;	// L57
  row_id = 0;	// L58
  int32_t col_id;	// L59
  col_id = 0;	// L60
  ap_uint<26> oe_r;	// L61
  oe_r = 0;	// L62
  ap_uint<26> ow_r;	// L63
  ow_r = 0;	// L64
  ap_uint<26> on_r;	// L65
  on_r = 0;	// L66
  ap_uint<26> os_r;	// L67
  os_r = 0;	// L68
  ap_uint<17> txn_r;	// L69
  txn_r = 0;	// L70
  ap_uint<17> txs_r;	// L71
  txs_r = 0;	// L72
  ap_uint<17> txw_r;	// L73
  txw_r = 0;	// L74
  ap_uint<17> txe_r;	// L75
  txe_r = 0;	// L76
  half hold_v[4][2];	// L77
  for (int v50 = 0; v50 < 4; v50++) {	// L78
    for (int v51 = 0; v51 < 2; v51++) {	// L78
      hold_v[v50][v51] = (double)0.000000;	// L78
    }
  }
  int32_t hold_cnt[4];	// L79
  for (int v53 = 0; v53 < 4; v53++) {	// L80
    hold_cnt[v53] = 0;	// L80
  }
  ap_uint<26> rbuf[4][2];	// L81
  for (int v55 = 0; v55 < 4; v55++) {	// L82
    for (int v56 = 0; v56 < 2; v56++) {	// L82
      rbuf[v55][v56] = 0;	// L82
    }
  }
  int32_t rbcnt[4];	// L83
  for (int v58 = 0; v58 < 4; v58++) {	// L84
    rbcnt[v58] = 0;	// L84
  }
  int32_t rcred[4];	// L85
  for (int v60 = 0; v60 < 4; v60++) {	// L86
    rcred[v60] = 0;	// L86
  }
  int32_t cre_r;	// L87
  cre_r = 2;	// L88
  int32_t crw_r;	// L89
  crw_r = 2;	// L90
  int32_t crs_r;	// L91
  crs_r = 2;	// L92
  int32_t crn_r;	// L93
  crn_r = 2;	// L94
  int32_t cfg_isz;	// L95
  cfg_isz = 0;	// L96
  int32_t cfg_itsz;	// L97
  cfg_itsz = 0;	// L98
  int32_t fetch_en;	// L99
  fetch_en = 0;	// L100
  int32_t instr_cnt;	// L101
  instr_cnt = 0;	// L102
  int32_t iter_cnt;	// L103
  iter_cnt = 0;	// L104
  int32_t condition_reg;	// L105
  condition_reg = 0;	// L106
  ap_int<26> v71 = oe_r;	// L107
  v0.write(v71);	// L108
  ap_int<26> v72 = ow_r;	// L109
  v1.write(v72);	// L110
  ap_int<26> v73 = os_r;	// L111
  v2.write(v73);	// L112
  ap_int<26> v74 = on_r;	// L113
  v3.write(v74);	// L114
  ap_int<17> v75 = txe_r;	// L115
  v4.write(v75);	// L116
  ap_int<17> v76 = txw_r;	// L117
  v5.write(v76);	// L118
  ap_int<17> v77 = txs_r;	// L119
  v6.write(v77);	// L120
  ap_int<17> v78 = txn_r;	// L121
  v7.write(v78);	// L122
  int32_t v79 = cre_r;	// L123
  v8.write(v79);	// L124
  int32_t v80 = crw_r;	// L125
  v9.write(v80);	// L126
  int32_t v81 = crs_r;	// L127
  v10.write(v81);	// L128
  int32_t v82 = crn_r;	// L129
  v11.write(v82);	// L130
  l_S_t_0_t: for (int t = 0; t < 10; t++) {	// L131
    ap_uint<26> v84 = v12.read();	// L132
    ap_uint<26> p_w;	// L133
    p_w = v84;	// L134
    ap_uint<26> v86 = v13.read();	// L135
    ap_uint<26> p_e;	// L136
    p_e = v86;	// L137
    ap_uint<26> v88 = v14.read();	// L138
    ap_uint<26> p_n;	// L139
    p_n = v88;	// L140
    ap_uint<26> v90 = v15.read();	// L141
    ap_uint<26> p_s;	// L142
    p_s = v90;	// L143
    int32_t v92 = v16.read();	// L144
    int32_t v93 = rcred[0];	// L145
    ap_int<33> v94 = v93;	// L146
    ap_int<33> v95 = v92;	// L147
    ap_int<33> v96 = v94 + v95;	// L148
    int32_t v97 = v96;	// L149
    rcred[0] = v97;	// L150
    int32_t v98 = v17.read();	// L151
    int32_t v99 = rcred[1];	// L152
    ap_int<33> v100 = v99;	// L153
    ap_int<33> v101 = v98;	// L154
    ap_int<33> v102 = v100 + v101;	// L155
    int32_t v103 = v102;	// L156
    rcred[1] = v103;	// L157
    int32_t v104 = v18.read();	// L158
    int32_t v105 = rcred[2];	// L159
    ap_int<33> v106 = v105;	// L160
    ap_int<33> v107 = v104;	// L161
    ap_int<33> v108 = v106 + v107;	// L162
    int32_t v109 = v108;	// L163
    rcred[2] = v109;	// L164
    int32_t v110 = v19.read();	// L165
    int32_t v111 = rcred[3];	// L166
    ap_int<33> v112 = v111;	// L167
    ap_int<33> v113 = v110;	// L168
    ap_int<33> v114 = v112 + v113;	// L169
    int32_t v115 = v114;	// L170
    rcred[3] = v115;	// L171
    ap_uint<26> fin[4];	// L172
    for (int v117 = 0; v117 < 4; v117++) {	// L173
      fin[v117] = 0;	// L173
    }
    ap_int<26> v118 = p_w;	// L174
    fin[0] = v118;	// L175
    ap_int<26> v119 = p_e;	// L176
    fin[1] = v119;	// L177
    ap_int<26> v120 = p_n;	// L178
    fin[2] = v120;	// L179
    ap_int<26> v121 = p_s;	// L180
    fin[3] = v121;	// L181
    l_S_d_0_d: for (int d = 0; d < 4; d++) {	// L182
      ap_uint<26> v123 = fin[d];	// L183
      bool v124;
      ap_int<26> v124_tmp = v123;
      v124 = v124_tmp[25];	// L184
      int32_t v125 = v124;	// L185
      bool v126 = v125 == 1;	// L186
      int32_t v127 = rbcnt[d];	// L187
      bool v128 = v127 < 2;	// L188
      bool v129 = v126 & v128;	// L189
      if (v129) {	// L190
        ap_uint<26> v130 = fin[d];	// L191
        int32_t v131 = rbcnt[d];	// L192
        int v132 = v131;	// L193
        rbuf[d][v132] = v130;	// L194
        int32_t v133 = rbcnt[d];	// L195
        ap_int<33> v134 = v133;	// L196
        ap_int<33> v135 = v134 + 1;	// L197
        int32_t v136 = v135;	// L198
        rbcnt[d] = v136;	// L199
      }
    }
    ap_uint<26> hd[4];	// L202
    for (int v138 = 0; v138 < 4; v138++) {	// L203
      hd[v138] = 0;	// L203
    }
    int32_t hvld[4];	// L204
    for (int v140 = 0; v140 < 4; v140++) {	// L205
      hvld[v140] = 0;	// L205
    }
    int32_t hit[4];	// L206
    for (int v142 = 0; v142 < 4; v142++) {	// L207
      hit[v142] = 0;	// L207
    }
    int32_t axis[4];	// L208
    for (int v144 = 0; v144 < 4; v144++) {	// L209
      axis[v144] = 0;	// L209
    }
    int32_t v145 = col_id;	// L210
    axis[0] = v145;	// L211
    int32_t v146 = col_id;	// L212
    axis[1] = v146;	// L213
    int32_t v147 = row_id;	// L214
    axis[2] = v147;	// L215
    int32_t v148 = row_id;	// L216
    axis[3] = v148;	// L217
    l_S_d_1_d1: for (int d1 = 0; d1 < 4; d1++) {	// L218
      int32_t v150 = rbcnt[d1];	// L219
      bool v151 = v150 > 0;	// L220
      if (v151) {	// L221
        ap_uint<26> v152 = rbuf[d1][0];	// L222
        hd[d1] = v152;	// L223
        hvld[d1] = 1;	// L224
        ap_uint<26> v153 = hd[d1];	// L225
        ap_int<4> v154;
        ap_int<26> v154_tmp = v153;
        v154 = v154_tmp(24, 21);	// L226
        int32_t v155 = axis[d1];	// L227
        int32_t v156 = v154;	// L228
        bool v157 = v156 == v155;	// L229
        if (v157) {	// L230
          hit[d1] = 1;	// L231
        }
      }
    }
    ap_uint<26> o_crv;	// L235
    o_crv = 0;	// L236
    int32_t crv_in;	// L237
    crv_in = -1;	// L238
    int32_t v160 = hit[3];	// L239
    bool v161 = v160 == 1;	// L240
    if (v161) {	// L241
      ap_uint<26> v162 = hd[3];	// L242
      o_crv = v162;	// L243
      crv_in = 3;	// L244
    } else {
      int32_t v163 = hit[2];	// L246
      bool v164 = v163 == 1;	// L247
      if (v164) {	// L248
        ap_uint<26> v165 = hd[2];	// L249
        o_crv = v165;	// L250
        crv_in = 2;	// L251
      } else {
        int32_t v166 = hit[1];	// L253
        bool v167 = v166 == 1;	// L254
        if (v167) {	// L255
          ap_uint<26> v168 = hd[1];	// L256
          o_crv = v168;	// L257
          crv_in = 1;	// L258
        } else {
          int32_t v169 = hit[0];	// L260
          bool v170 = v169 == 1;	// L261
          if (v170) {	// L262
            ap_uint<26> v171 = hd[0];	// L263
            o_crv = v171;	// L264
            crv_in = 0;	// L265
          }
        }
      }
    }
    ap_uint<26> o_out[4];	// L270
    for (int v173 = 0; v173 < 4; v173++) {	// L271
      o_out[v173] = 0;	// L271
    }
    int32_t pop[4];	// L272
    for (int v175 = 0; v175 < 4; v175++) {	// L273
      pop[v175] = 0;	// L273
    }
    int32_t inj_done;	// L274
    inj_done = 0;	// L275
    int32_t idir;	// L276
    idir = -1;	// L277
    ap_int<26> v178 = csd_pkt;	// L278
    bool v179;
    ap_int<26> v179_tmp = v178;
    v179 = v179_tmp[25];	// L279
    int32_t v180 = v179;	// L280
    bool v181 = v180 == 1;	// L281
    if (v181) {	// L282
      int32_t v182 = csd_dir;	// L283
      ap_int<33> v183 = v182;	// L284
      ap_int<33> v184 = 3 - v183;	// L285
      int32_t v185 = v184;	// L286
      idir = v185;	// L287
    }
    l_S_o_2_o: for (int o = 0; o < 4; o++) {	// L289
      int32_t v187 = rcred[o];	// L290
      bool v188 = v187 > 0;	// L291
      if (v188) {	// L292
        int32_t v189 = idir;	// L293
        ap_int<33> v190 = v189;	// L294
        ap_int<33> v191 = o;	// L295
        bool v192 = v190 == v191;	// L296
        if (v192) {	// L297
          ap_int<26> v193 = csd_pkt;	// L298
          o_out[o] = v193;	// L299
          int32_t v194 = rcred[o];	// L300
          ap_int<33> v195 = v194;	// L301
          ap_int<33> v196 = v195 - 1;	// L302
          int32_t v197 = v196;	// L303
          rcred[o] = v197;	// L304
          inj_done = 1;	// L305
        } else {
          int32_t v198 = hvld[o];	// L307
          bool v199 = v198 == 1;	// L308
          int32_t v200 = hit[o];	// L309
          bool v201 = v200 == 0;	// L310
          bool v202 = v199 & v201;	// L311
          if (v202) {	// L312
            ap_uint<26> v203 = hd[o];	// L313
            o_out[o] = v203;	// L314
            int32_t v204 = rcred[o];	// L315
            ap_int<33> v205 = v204;	// L316
            ap_int<33> v206 = v205 - 1;	// L317
            int32_t v207 = v206;	// L318
            rcred[o] = v207;	// L319
            pop[o] = 1;	// L320
          }
        }
      }
    }
    int32_t v208 = crv_in;	// L325
    bool v209 = v208 >= 0;	// L326
    if (v209) {	// L327
      int32_t v210 = crv_in;	// L328
      int v211 = v210;	// L329
      pop[v211] = 1;	// L330
    }
    int32_t ret[4];	// L332
    for (int v213 = 0; v213 < 4; v213++) {	// L333
      ret[v213] = 0;	// L333
    }
    l_S_d_3_d2: for (int d2 = 0; d2 < 4; d2++) {	// L334
      int32_t v215 = pop[d2];	// L335
      bool v216 = v215 == 1;	// L336
      if (v216) {	// L337
        l_S_sft_3_sft: for (int sft = 0; sft < 1; sft++) {	// L338
          ap_uint<26> v218 = rbuf[d2][(sft + 1)];	// L339
          rbuf[d2][sft] = v218;	// L340
        }
        int32_t v219 = rbcnt[d2];	// L342
        ap_int<33> v220 = v219;	// L343
        ap_int<33> v221 = v220 - 1;	// L344
        int32_t v222 = v221;	// L345
        rbcnt[d2] = v222;	// L346
        ret[d2] = 1;	// L347
      }
    }
    int32_t v223 = ret[0];	// L350
    cre_r = v223;	// L351
    int32_t v224 = ret[1];	// L352
    crw_r = v224;	// L353
    int32_t v225 = ret[2];	// L354
    crs_r = v225;	// L355
    int32_t v226 = ret[3];	// L356
    crn_r = v226;	// L357
    ap_uint<26> v227 = o_out[0];	// L358
    oe_r = v227;	// L359
    ap_uint<26> v228 = o_out[1];	// L360
    ow_r = v228;	// L361
    ap_uint<26> v229 = o_out[2];	// L362
    os_r = v229;	// L363
    ap_uint<26> v230 = o_out[3];	// L364
    on_r = v230;	// L365
    int32_t v231 = inj_done;	// L366
    bool v232 = v231 == 1;	// L367
    if (v232) {	// L368
      csd_pkt = 0;	// L369
    }
    ap_int<26> v233 = o_crv;	// L371
    bool v234;
    ap_int<26> v234_tmp = v233;
    v234 = v234_tmp[25];	// L372
    int32_t v235 = v234;	// L373
    crv_vld = v235;	// L374
    ap_int<26> v236 = o_crv;	// L375
    int16_t v237;
    ap_int<26> v237_tmp = v236;
    v237 = v237_tmp(15, 0);	// L376
    half v238;
    union { uint16_t from; half to;} _converter_v237_to_v238;
    _converter_v237_to_v238.from = v237;
    v238 = _converter_v237_to_v238.to;	// L377
    crv_data = v238;	// L378
    ap_int<26> v239 = o_crv;	// L379
    ap_int<4> v240;
    ap_int<26> v240_tmp = v239;
    v240 = v240_tmp(19, 16);	// L380
    int32_t v241 = v240;	// L381
    crv_addr = v241;	// L382
    ap_int<26> v242 = o_crv;	// L383
    bool v243;
    ap_int<26> v243_tmp = v242;
    v243 = v243_tmp[20];	// L384
    int32_t v244 = v243;	// L385
    crv_mode = v244;	// L386
    ap_int<26> v245 = o_crv;	// L387
    int16_t v246;
    ap_int<26> v246_tmp = v245;
    v246 = v246_tmp(15, 0);	// L388
    int32_t v247 = v246;	// L389
    crv_raw = v247;	// L390
    ap_uint<17> v248 = v20.read();	// L391
    ap_uint<17> rx_w;	// L392
    rx_w = v248;	// L393
    ap_uint<17> v250 = v21.read();	// L394
    ap_uint<17> rx_e;	// L395
    rx_e = v250;	// L396
    ap_uint<17> v252 = v22.read();	// L397
    ap_uint<17> rx_n;	// L398
    rx_n = v252;	// L399
    ap_uint<17> v254 = v23.read();	// L400
    ap_uint<17> rx_s;	// L401
    rx_s = v254;	// L402
    half rxv[4];	// L403
    for (int v257 = 0; v257 < 4; v257++) {	// L404
      rxv[v257] = (double)0.000000;	// L404
    }
    int32_t rxvld[4];	// L405
    for (int v259 = 0; v259 < 4; v259++) {	// L406
      rxvld[v259] = 0;	// L406
    }
    ap_int<17> v260 = rx_n;	// L407
    int16_t v261;
    ap_int<17> v261_tmp = v260;
    v261 = v261_tmp(16, 1);	// L408
    half v262;
    union { uint16_t from; half to;} _converter_v261_to_v262;
    _converter_v261_to_v262.from = v261;
    v262 = _converter_v261_to_v262.to;	// L409
    rxv[0] = v262;	// L410
    ap_int<17> v263 = rx_n;	// L411
    bool v264;
    ap_int<17> v264_tmp = v263;
    v264 = v264_tmp[0];	// L412
    int32_t v265 = v264;	// L413
    rxvld[0] = v265;	// L414
    ap_int<17> v266 = rx_s;	// L415
    int16_t v267;
    ap_int<17> v267_tmp = v266;
    v267 = v267_tmp(16, 1);	// L416
    half v268;
    union { uint16_t from; half to;} _converter_v267_to_v268;
    _converter_v267_to_v268.from = v267;
    v268 = _converter_v267_to_v268.to;	// L417
    rxv[1] = v268;	// L418
    ap_int<17> v269 = rx_s;	// L419
    bool v270;
    ap_int<17> v270_tmp = v269;
    v270 = v270_tmp[0];	// L420
    int32_t v271 = v270;	// L421
    rxvld[1] = v271;	// L422
    ap_int<17> v272 = rx_w;	// L423
    int16_t v273;
    ap_int<17> v273_tmp = v272;
    v273 = v273_tmp(16, 1);	// L424
    half v274;
    union { uint16_t from; half to;} _converter_v273_to_v274;
    _converter_v273_to_v274.from = v273;
    v274 = _converter_v273_to_v274.to;	// L425
    rxv[2] = v274;	// L426
    ap_int<17> v275 = rx_w;	// L427
    bool v276;
    ap_int<17> v276_tmp = v275;
    v276 = v276_tmp[0];	// L428
    int32_t v277 = v276;	// L429
    rxvld[2] = v277;	// L430
    ap_int<17> v278 = rx_e;	// L431
    int16_t v279;
    ap_int<17> v279_tmp = v278;
    v279 = v279_tmp(16, 1);	// L432
    half v280;
    union { uint16_t from; half to;} _converter_v279_to_v280;
    _converter_v279_to_v280.from = v279;
    v280 = _converter_v279_to_v280.to;	// L433
    rxv[3] = v280;	// L434
    ap_int<17> v281 = rx_e;	// L435
    bool v282;
    ap_int<17> v282_tmp = v281;
    v282 = v282_tmp[0];	// L436
    int32_t v283 = v282;	// L437
    rxvld[3] = v283;	// L438
    l_S_d_5_d3: for (int d3 = 0; d3 < 4; d3++) {	// L439
      int32_t v285 = rxvld[d3];	// L440
      bool v286 = v285 == 1;	// L441
      int32_t v287 = hold_cnt[d3];	// L442
      bool v288 = v287 < 2;	// L443
      bool v289 = v286 & v288;	// L444
      if (v289) {	// L445
        half v290 = rxv[d3];	// L446
        int32_t v291 = hold_cnt[d3];	// L447
        int v292 = v291;	// L448
        hold_v[d3][v292] = v290;	// L449
        int32_t v293 = hold_cnt[d3];	// L450
        ap_int<33> v294 = v293;	// L451
        ap_int<33> v295 = v294 + 1;	// L452
        int32_t v296 = v295;	// L453
        hold_cnt[d3] = v296;	// L454
      }
    }
    int32_t pc;	// L457
    pc = -1;	// L458
    int32_t v298 = fetch_en;	// L459
    bool v299 = v298 == 1;	// L460
    if (v299) {	// L461
      int32_t v300 = instr_cnt;	// L462
      pc = v300;	// L463
    }
    int32_t instr;	// L465
    instr = 0;	// L466
    int32_t v302 = pc;	// L467
    bool v303 = v302 >= 0;	// L468
    if (v303) {	// L469
      int32_t v304 = pc;	// L470
      int v305 = v304;	// L471
      int32_t v306 = irf[v305];	// L472
      instr = v306;	// L473
    }
    int32_t v307 = instr;	// L475
    int32_t v308 = v307 & 15;	// L476
    int32_t op;	// L477
    op = v308;	// L478
    int32_t v310 = instr;	// L479
    int32_t v311 = v310 >> 4;	// L480
    int32_t v312 = v311 & 15;	// L481
    int32_t dst;	// L482
    dst = v312;	// L483
    int32_t v314 = instr;	// L484
    int32_t v315 = v314 >> 8;	// L485
    int32_t v316 = v315 & 15;	// L486
    int32_t s1;	// L487
    s1 = v316;	// L488
    int32_t v318 = instr;	// L489
    int32_t v319 = v318 >> 12;	// L490
    int32_t v320 = v319 & 15;	// L491
    int32_t s2;	// L492
    s2 = v320;	// L493
    half a;	// L494
    a = (double)0.000000;	// L495
    half b;	// L496
    b = (double)0.000000;	// L497
    int32_t v324 = s1;	// L498
    bool v325 = v324 >= 12;	// L499
    if (v325) {	// L500
      int32_t v326 = s1;	// L501
      int32_t v327 = v326 & 3;	// L502
      int v328 = v327;	// L503
      half v329 = hold_v[v328][0];	// L504
      a = v329;	// L505
    } else {
      int32_t v330 = s1;	// L507
      int v331 = v330;	// L508
      half v332 = drf[v331];	// L509
      a = v332;	// L510
    }
    int32_t v333 = s2;	// L512
    bool v334 = v333 >= 12;	// L513
    if (v334) {	// L514
      int32_t v335 = s2;	// L515
      int32_t v336 = v335 & 3;	// L516
      int v337 = v336;	// L517
      half v338 = hold_v[v337][0];	// L518
      b = v338;	// L519
    } else {
      int32_t v339 = s2;	// L521
      int v340 = v339;	// L522
      half v341 = drf[v340];	// L523
      b = v341;	// L524
    }
    int32_t a_vld;	// L526
    a_vld = 1;	// L527
    int32_t b_vld;	// L528
    b_vld = 1;	// L529
    int32_t v344 = s1;	// L530
    bool v345 = v344 >= 12;	// L531
    if (v345) {	// L532
      a_vld = 0;	// L533
      int32_t v346 = s1;	// L534
      int32_t v347 = v346 & 3;	// L535
      int v348 = v347;	// L536
      int32_t v349 = hold_cnt[v348];	// L537
      bool v350 = v349 > 0;	// L538
      if (v350) {	// L539
        a_vld = 1;	// L540
      }
    }
    int32_t v351 = s2;	// L543
    bool v352 = v351 >= 12;	// L544
    if (v352) {	// L545
      b_vld = 0;	// L546
      int32_t v353 = s2;	// L547
      int32_t v354 = v353 & 3;	// L548
      int v355 = v354;	// L549
      int32_t v356 = hold_cnt[v355];	// L550
      bool v357 = v356 > 0;	// L551
      if (v357) {	// L552
        b_vld = 1;	// L553
      }
    }
    int32_t v358 = s1;	// L556
    bool v359 = v358 < 8;	// L557
    int32_t v360 = dsmask;	// L558
    int32_t v361 = v360 >> v358;	// L560
    int32_t v362 = v361 & 1;	// L561
    bool v363 = v362 == 1;	// L562
    bool v364 = v359 & v363;	// L563
    if (v364) {	// L564
      int32_t v365 = s1;	// L565
      int v366 = v365;	// L566
      int32_t v367 = drf_full[v366];	// L567
      bool v368 = v367 == 0;	// L568
      if (v368) {	// L569
        a_vld = 0;	// L570
      }
    }
    int32_t v369 = s2;	// L573
    bool v370 = v369 < 8;	// L574
    int32_t v371 = dsmask;	// L575
    int32_t v372 = v371 >> v369;	// L577
    int32_t v373 = v372 & 1;	// L578
    bool v374 = v373 == 1;	// L579
    bool v375 = v370 & v374;	// L580
    if (v375) {	// L581
      int32_t v376 = s2;	// L582
      int v377 = v376;	// L583
      int32_t v378 = drf_full[v377];	// L584
      bool v379 = v378 == 0;	// L585
      if (v379) {	// L586
        b_vld = 0;	// L587
      }
    }
    int32_t binop;	// L590
    binop = 0;	// L591
    int32_t v381 = op;	// L592
    bool v382 = v381 == 0;	// L593
    bool v383 = v381 == 1;	// L595
    bool v384 = v381 == 2;	// L597
    bool v385 = v381 == 8;	// L599
    bool v386 = v381 == 9;	// L601
    bool v387 = v382 | v383;	// L602
    bool v388 = v387 | v384;	// L603
    bool v389 = v388 | v385;	// L604
    bool v390 = v389 | v386;	// L605
    if (v390) {	// L606
      binop = 1;	// L607
    }
    int32_t grant;	// L609
    grant = 0;	// L610
    int32_t v392 = pc;	// L611
    bool v393 = v392 >= 0;	// L612
    if (v393) {	// L613
      grant = 1;	// L614
    }
    int32_t v394 = pc;	// L616
    bool v395 = v394 >= 0;	// L617
    int32_t v396 = a_vld;	// L618
    bool v397 = v396 == 0;	// L619
    int32_t v398 = binop;	// L620
    bool v399 = v398 == 1;	// L621
    int32_t v400 = b_vld;	// L622
    bool v401 = v400 == 0;	// L623
    bool v402 = v399 & v401;	// L624
    bool v403 = v397 | v402;	// L625
    bool v404 = v395 & v403;	// L626
    if (v404) {	// L627
      grant = 0;	// L628
    }
    int32_t v405 = grant;	// L630
    bool v406 = v405 == 1;	// L631
    if (v406) {	// L632
      int32_t v407 = instr_cnt;	// L633
      int32_t v408 = cfg_isz;	// L634
      bool v409 = v407 == v408;	// L635
      if (v409) {	// L636
        instr_cnt = 0;	// L637
        int32_t v410 = iter_cnt;	// L638
        int32_t v411 = cfg_itsz;	// L639
        ap_int<33> v412 = v411;	// L640
        ap_int<33> v413 = v412 - 1;	// L641
        ap_int<33> v414 = v410;	// L642
        bool v415 = v414 == v413;	// L643
        if (v415) {	// L644
          fetch_en = 0;	// L645
        } else {
          int32_t v416 = iter_cnt;	// L647
          ap_int<33> v417 = v416;	// L648
          ap_int<33> v418 = v417 + 1;	// L649
          int32_t v419 = v418;	// L650
          iter_cnt = v419;	// L651
        }
      } else {
        int32_t v420 = instr_cnt;	// L654
        ap_int<33> v421 = v420;	// L655
        ap_int<33> v422 = v421 + 1;	// L656
        int32_t v423 = v422;	// L657
        instr_cnt = v423;	// L658
      }
    }
    int32_t c1;	// L661
    c1 = -1;	// L662
    int32_t c2;	// L663
    c2 = -1;	// L664
    int32_t v426 = grant;	// L665
    bool v427 = v426 == 1;	// L666
    int32_t v428 = s1;	// L667
    bool v429 = v428 >= 12;	// L668
    bool v430 = v427 & v429;	// L669
    if (v430) {	// L670
      int32_t v431 = s1;	// L671
      int32_t v432 = v431 & 3;	// L672
      c1 = v432;	// L673
    }
    int32_t v433 = grant;	// L675
    bool v434 = v433 == 1;	// L676
    int32_t v435 = s2;	// L677
    bool v436 = v435 >= 12;	// L678
    bool v437 = v434 & v436;	// L679
    if (v437) {	// L680
      int32_t v438 = s2;	// L681
      int32_t v439 = v438 & 3;	// L682
      c2 = v439;	// L683
    }
    int32_t v440 = c1;	// L685
    bool v441 = v440 >= 0;	// L686
    if (v441) {	// L687
      int32_t v442 = c1;	// L688
      int v443 = v442;	// L689
      half v444 = hold_v[v443][1];	// L690
      hold_v[v443][0] = v444;	// L693
      int32_t v445 = c1;	// L694
      int v446 = v445;	// L695
      int32_t v447 = hold_cnt[v446];	// L696
      ap_int<33> v448 = v447;	// L697
      ap_int<33> v449 = v448 - 1;	// L698
      int32_t v450 = v449;	// L699
      hold_cnt[v446] = v450;	// L702
    }
    int32_t v451 = c2;	// L704
    bool v452 = v451 >= 0;	// L705
    int32_t v453 = c1;	// L707
    bool v454 = v451 != v453;	// L708
    bool v455 = v452 & v454;	// L709
    if (v455) {	// L710
      int32_t v456 = c2;	// L711
      int v457 = v456;	// L712
      half v458 = hold_v[v457][1];	// L713
      hold_v[v457][0] = v458;	// L716
      int32_t v459 = c2;	// L717
      int v460 = v459;	// L718
      int32_t v461 = hold_cnt[v460];	// L719
      ap_int<33> v462 = v461;	// L720
      ap_int<33> v463 = v462 - 1;	// L721
      int32_t v464 = v463;	// L722
      hold_cnt[v460] = v464;	// L725
    }
    int32_t v465 = grant;	// L727
    bool v466 = v465 == 1;	// L728
    int32_t v467 = s1;	// L729
    bool v468 = v467 < 8;	// L730
    int32_t v469 = dsmask;	// L731
    int32_t v470 = v469 >> v467;	// L733
    int32_t v471 = v470 & 1;	// L734
    bool v472 = v471 == 1;	// L735
    bool v473 = v466 & v468;	// L736
    bool v474 = v473 & v472;	// L737
    if (v474) {	// L738
      int32_t v475 = s1;	// L739
      int v476 = v475;	// L740
      drf_full[v476] = 0;	// L741
    }
    int32_t v477 = grant;	// L743
    bool v478 = v477 == 1;	// L744
    int32_t v479 = s2;	// L745
    bool v480 = v479 < 8;	// L746
    int32_t v481 = dsmask;	// L747
    int32_t v482 = v481 >> v479;	// L749
    int32_t v483 = v482 & 1;	// L750
    bool v484 = v483 == 1;	// L751
    bool v485 = v478 & v480;	// L752
    bool v486 = v485 & v484;	// L753
    if (v486) {	// L754
      int32_t v487 = s2;	// L755
      int v488 = v487;	// L756
      drf_full[v488] = 0;	// L757
    }
    half res;	// L759
    res = (double)0.000000;	// L760
    int32_t v490 = op;	// L761
    bool v491 = v490 == 0;	// L762
    if (v491) {	// L763
      half v492 = a;	// L764
      half v493 = b;	// L765
      half v494 = v492 + v493;	// L766
      res = v494;	// L767
    } else {
      int32_t v495 = op;	// L769
      bool v496 = v495 == 1;	// L770
      if (v496) {	// L771
        half v497 = a;	// L772
        half v498 = b;	// L773
        half v499 = v497 - v498;	// L774
        res = v499;	// L775
      } else {
        int32_t v500 = op;	// L777
        bool v501 = v500 == 2;	// L778
        if (v501) {	// L779
          half v502 = a;	// L780
          half v503 = b;	// L781
          half v504 = v502 * v503;	// L782
          res = v504;	// L783
        } else {
          int32_t v505 = op;	// L785
          bool v506 = v505 == 8;	// L786
          if (v506) {	// L787
            half v507 = a;	// L788
            half v508 = b;	// L789
            bool v509 = v507 >= v508;	// L790
            if (v509) {	// L791
              res = (double)1.000000;	// L792
            } else {
              res = (double)-1.000000;	// L794
            }
          } else {
            int32_t v510 = op;	// L797
            bool v511 = v510 == 9;	// L798
            if (v511) {	// L799
              half v512 = a;	// L800
              half v513 = b;	// L801
              bool v514 = v512 < v513;	// L802
              if (v514) {	// L803
                res = (double)1.000000;	// L804
              } else {
                res = (double)-1.000000;	// L806
              }
            } else {
              half v515 = a;	// L809
              res = v515;	// L810
            }
          }
        }
      }
    }
    int32_t v516 = a_vld;	// L816
    int32_t res_vld;	// L817
    res_vld = v516;	// L818
    int32_t v518 = op;	// L819
    bool v519 = v518 == 0;	// L820
    bool v520 = v518 == 1;	// L822
    bool v521 = v518 == 2;	// L824
    bool v522 = v518 == 8;	// L826
    bool v523 = v518 == 9;	// L828
    bool v524 = v519 | v520;	// L829
    bool v525 = v524 | v521;	// L830
    bool v526 = v525 | v522;	// L831
    bool v527 = v526 | v523;	// L832
    if (v527) {	// L833
      int32_t v528 = a_vld;	// L834
      int32_t v529 = b_vld;	// L835
      int64_t v530 = v528;	// L836
      int64_t v531 = v529;	// L837
      int64_t v532 = v530 * v531;	// L838
      int32_t v533 = v532;	// L839
      res_vld = v533;	// L840
    }
    int32_t v534 = grant;	// L842
    bool v535 = v534 == 0;	// L843
    if (v535) {	// L844
      res_vld = 0;	// L845
    }
    int32_t v536 = grant;	// L847
    bool v537 = v536 == 1;	// L848
    int32_t v538 = op;	// L849
    bool v539 = v538 == 8;	// L850
    bool v540 = v537 & v539;	// L851
    if (v540) {	// L852
      condition_reg = 0;	// L853
      half v541 = a;	// L854
      half v542 = b;	// L855
      bool v543 = v541 >= v542;	// L856
      if (v543) {	// L857
        condition_reg = 1;	// L858
      }
    }
    int32_t v544 = grant;	// L861
    bool v545 = v544 == 1;	// L862
    int32_t v546 = op;	// L863
    bool v547 = v546 == 9;	// L864
    bool v548 = v545 & v547;	// L865
    if (v548) {	// L866
      condition_reg = 0;	// L867
      half v549 = a;	// L868
      half v550 = b;	// L869
      bool v551 = v549 < v550;	// L870
      if (v551) {	// L871
        condition_reg = 1;	// L872
      }
    }
    ap_uint<17> tx_n;	// L875
    tx_n = 0;	// L876
    ap_uint<17> tx_s;	// L877
    tx_s = 0;	// L878
    ap_uint<17> tx_w;	// L879
    tx_w = 0;	// L880
    ap_uint<17> tx_e;	// L881
    tx_e = 0;	// L882
    int32_t is_rtr;	// L883
    is_rtr = 0;	// L884
    int32_t do_inj;	// L885
    do_inj = 0;	// L886
    int32_t v558 = op;	// L887
    bool v559 = v558 >= 4;	// L888
    ap_int<33> v560 = v558;	// L890
    bool v561 = v560 <= 7;	// L891
    bool v562 = v559 & v561;	// L892
    if (v562) {	// L893
      is_rtr = 1;	// L894
      do_inj = 1;	// L895
    }
    int32_t v563 = op;	// L897
    bool v564 = v563 >= 12;	// L898
    ap_int<33> v565 = v563;	// L900
    bool v566 = v565 <= 15;	// L901
    bool v567 = v564 & v566;	// L902
    if (v567) {	// L903
      is_rtr = 1;	// L904
      int32_t v568 = condition_reg;	// L905
      bool v569 = v568 == 1;	// L906
      if (v569) {	// L907
        do_inj = 1;	// L908
      }
    }
    int32_t v570 = is_rtr;	// L911
    bool v571 = v570 == 1;	// L912
    if (v571) {	// L913
      int32_t v572 = do_inj;	// L914
      bool v573 = v572 == 1;	// L915
      ap_int<26> v574 = csd_pkt;	// L916
      bool v575;
      ap_int<26> v575_tmp = v574;
      v575 = v575_tmp[25];	// L917
      int32_t v576 = v575;	// L918
      bool v577 = v576 == 0;	// L919
      bool v578 = v573 & v577;	// L920
      if (v578) {	// L921
        half v579 = res;	// L922
        uint16_t v580;
        union { half from; uint16_t to;} _converter_v579_to_v580;
        _converter_v579_to_v580.from = v579;
        v580 = _converter_v579_to_v580.to;	// L923
        ap_int<26> v581 = csd_pkt;	// L924
        ap_int<26> v582;
        ap_int<26> v582_tmp = v581;
        v582_tmp(15, 0) = v580;
        v582 = v582_tmp;	// L925
        csd_pkt = v582;	// L926
        int32_t v583 = dst;	// L927
        ap_uint<4> v584 = v583;	// L928
        ap_int<26> v585 = csd_pkt;	// L929
        ap_int<26> v586;
        ap_int<26> v586_tmp = v585;
        v586_tmp(19, 16) = v584;
        v586 = v586_tmp;	// L930
        csd_pkt = v586;	// L931
        int32_t v587 = s2;	// L932
        ap_uint<4> v588 = v587;	// L933
        ap_int<26> v589 = csd_pkt;	// L934
        ap_int<26> v590;
        ap_int<26> v590_tmp = v589;
        v590_tmp(24, 21) = v588;
        v590 = v590_tmp;	// L935
        csd_pkt = v590;	// L936
        int32_t v591 = res_vld;	// L937
        bool v592 = v591;	// L938
        ap_int<26> v593 = csd_pkt;	// L939
        ap_int<26> v594;
        ap_int<26> v594_tmp = v593;
        v594_tmp[25] = v592;        v594 = v594_tmp;	// L940
        csd_pkt = v594;	// L941
        int32_t v595 = op;	// L942
        int32_t v596 = v595 & 3;	// L943
        csd_dir = v596;	// L944
      }
    } else {
      int32_t v597 = dst;	// L947
      bool v598 = v597 >= 12;	// L948
      if (v598) {	// L949
        ap_uint<17> tw;	// L950
        tw = 0;	// L951
        int32_t v600 = res_vld;	// L952
        bool v601 = v600;	// L953
        ap_int<17> v602 = tw;	// L954
        ap_int<17> v603;
        ap_int<17> v603_tmp = v602;
        v603_tmp[0] = v601;        v603 = v603_tmp;	// L955
        tw = v603;	// L956
        half v604 = res;	// L957
        uint16_t v605;
        union { half from; uint16_t to;} _converter_v604_to_v605;
        _converter_v604_to_v605.from = v604;
        v605 = _converter_v604_to_v605.to;	// L958
        ap_int<17> v606 = tw;	// L959
        ap_int<17> v607;
        ap_int<17> v607_tmp = v606;
        v607_tmp(16, 1) = v605;
        v607 = v607_tmp;	// L960
        tw = v607;	// L961
        int32_t v608 = dst;	// L962
        int32_t v609 = v608 & 3;	// L963
        bool v610 = v609 == 0;	// L964
        if (v610) {	// L965
          ap_int<17> v611 = tw;	// L966
          tx_n = v611;	// L967
        } else {
          int32_t v612 = dst;	// L969
          int32_t v613 = v612 & 3;	// L970
          bool v614 = v613 == 1;	// L971
          if (v614) {	// L972
            ap_int<17> v615 = tw;	// L973
            tx_s = v615;	// L974
          } else {
            int32_t v616 = dst;	// L976
            int32_t v617 = v616 & 3;	// L977
            bool v618 = v617 == 2;	// L978
            if (v618) {	// L979
              ap_int<17> v619 = tw;	// L980
              tx_w = v619;	// L981
            } else {
              ap_int<17> v620 = tw;	// L983
              tx_e = v620;	// L984
            }
          }
        }
      } else {
        int32_t v621 = res_vld;	// L989
        bool v622 = v621 == 1;	// L990
        if (v622) {	// L991
          int32_t v623 = dst;	// L992
          bool v624 = v623 < 8;	// L993
          int32_t v625 = dsmask;	// L994
          int32_t v626 = v625 >> v623;	// L996
          int32_t v627 = v626 & 1;	// L997
          bool v628 = v627 == 1;	// L998
          bool v629 = v624 & v628;	// L999
          if (v629) {	// L1000
            int32_t v630 = dst;	// L1001
            int v631 = v630;	// L1002
            int32_t v632 = drf_full[v631];	// L1003
            bool v633 = v632 == 0;	// L1004
            if (v633) {	// L1005
              half v634 = res;	// L1006
              int32_t v635 = dst;	// L1007
              int v636 = v635;	// L1008
              drf[v636] = v634;	// L1009
              int32_t v637 = dst;	// L1010
              int v638 = v637;	// L1011
              drf_full[v638] = 1;	// L1012
            }
          } else {
            half v639 = res;	// L1015
            int32_t v640 = dst;	// L1016
            int v641 = v640;	// L1017
            drf[v641] = v639;	// L1018
          }
        }
      }
    }
    ap_int<17> v642 = tx_n;	// L1023
    txn_r = v642;	// L1024
    ap_int<17> v643 = tx_s;	// L1025
    txs_r = v643;	// L1026
    ap_int<17> v644 = tx_w;	// L1027
    txw_r = v644;	// L1028
    ap_int<17> v645 = tx_e;	// L1029
    txe_r = v645;	// L1030
    int32_t v646 = crv_vld;	// L1031
    bool v647 = v646 == 1;	// L1032
    if (v647) {	// L1033
      int32_t v648 = crv_mode;	// L1034
      bool v649 = v648 == 1;	// L1035
      if (v649) {	// L1036
        int32_t v650 = crv_addr;	// L1037
        int32_t v651 = v650 >> 3;	// L1038
        int32_t v652 = v651 & 1;	// L1039
        bool v653 = v652 == 1;	// L1040
        if (v653) {	// L1041
          int32_t v654 = crv_raw;	// L1042
          int32_t v655 = crv_addr;	// L1043
          int32_t v656 = v655 & 7;	// L1044
          int v657 = v656;	// L1045
          irf[v657] = v654;	// L1046
        } else {
          int32_t v658 = crv_addr;	// L1048
          bool v659 = v658 == 0;	// L1049
          if (v659) {	// L1050
            int32_t v660 = crv_raw;	// L1051
            int32_t v661 = v660 & 255;	// L1052
            dsmask = v661;	// L1053
            int32_t v662 = crv_raw;	// L1054
            int32_t v663 = v662 >> 8;	// L1055
            int32_t v664 = v663 & 7;	// L1056
            cfg_isz = v664;	// L1057
            int32_t v665 = crv_raw;	// L1058
            int32_t v666 = v665 >> 15;	// L1059
            int32_t v667 = v666 & 1;	// L1060
            bool v668 = v667 == 1;	// L1061
            if (v668) {	// L1062
              fetch_en = 1;	// L1063
              instr_cnt = 0;	// L1064
              iter_cnt = 0;	// L1065
            }
          } else {
            int32_t v669 = crv_addr;	// L1068
            bool v670 = v669 == 1;	// L1069
            if (v670) {	// L1070
              int32_t v671 = crv_raw;	// L1071
              int32_t v672 = v671 & 255;	// L1072
              cfg_itsz = v672;	// L1073
            }
          }
        }
      } else {
        int32_t v673 = crv_addr;	// L1078
        bool v674 = v673 < 8;	// L1079
        int32_t v675 = dsmask;	// L1080
        int32_t v676 = v675 >> v673;	// L1082
        int32_t v677 = v676 & 1;	// L1083
        bool v678 = v677 == 1;	// L1084
        bool v679 = v674 & v678;	// L1085
        if (v679) {	// L1086
          int32_t v680 = crv_addr;	// L1087
          int v681 = v680;	// L1088
          int32_t v682 = drf_full[v681];	// L1089
          bool v683 = v682 == 0;	// L1090
          if (v683) {	// L1091
            half v684 = crv_data;	// L1092
            int32_t v685 = crv_addr;	// L1093
            int v686 = v685;	// L1094
            drf[v686] = v684;	// L1095
            int32_t v687 = crv_addr;	// L1096
            int v688 = v687;	// L1097
            drf_full[v688] = 1;	// L1098
          }
        } else {
          half v689 = crv_data;	// L1101
          int32_t v690 = crv_addr;	// L1102
          int v691 = v690;	// L1103
          drf[v691] = v689;	// L1104
        }
      }
    }
    ap_int<26> v692 = oe_r;	// L1108
    v0.write(v692);	// L1109
    ap_int<26> v693 = ow_r;	// L1110
    v1.write(v693);	// L1111
    ap_int<26> v694 = os_r;	// L1112
    v2.write(v694);	// L1113
    ap_int<26> v695 = on_r;	// L1114
    v3.write(v695);	// L1115
    ap_int<17> v696 = txe_r;	// L1116
    v4.write(v696);	// L1117
    ap_int<17> v697 = txw_r;	// L1118
    v5.write(v697);	// L1119
    ap_int<17> v698 = txs_r;	// L1120
    v6.write(v698);	// L1121
    ap_int<17> v699 = txn_r;	// L1122
    v7.write(v699);	// L1123
    int32_t v700 = cre_r;	// L1124
    v8.write(v700);	// L1125
    int32_t v701 = crw_r;	// L1126
    v9.write(v701);	// L1127
    int32_t v702 = crs_r;	// L1128
    v10.write(v702);	// L1129
    int32_t v703 = crn_r;	// L1130
    v11.write(v703);	// L1131
  }
}

void drv_w_0(
  half v704[1][10],
  int32_t v705[1][10],
  hls::stream< ap_uint<17> >& v706
) {	// L1135
  l_S_t_0_t1: for (int t1 = 0; t1 < 10; t1++) {	// L1141
    ap_uint<17> w;	// L1142
    w = 0;	// L1143
    ap_int<33> v709 = t1;	// L1144
    bool v710 = v709 < 10;	// L1145
    if (v710) {	// L1146
      int32_t v711 = v705[0][t1];	// L1147
      bool v712 = v711;	// L1148
      ap_int<17> v713 = w;	// L1149
      ap_int<17> v714;
      ap_int<17> v714_tmp = v713;
      v714_tmp[0] = v712;      v714 = v714_tmp;	// L1150
      w = v714;	// L1151
      half v715 = v704[0][t1];	// L1152
      uint16_t v716;
      union { half from; uint16_t to;} _converter_v715_to_v716;
      _converter_v715_to_v716.from = v715;
      v716 = _converter_v715_to_v716.to;	// L1153
      ap_int<17> v717 = w;	// L1154
      ap_int<17> v718;
      ap_int<17> v718_tmp = v717;
      v718_tmp(16, 1) = v716;
      v718 = v718_tmp;	// L1155
      w = v718;	// L1156
    }
    ap_int<17> v719 = w;	// L1158
    v706.write(v719);	// L1159
  }
}

void drv_e_0(
  half v720[1][10],
  int32_t v721[1][10],
  hls::stream< ap_uint<17> >& v722
) {	// L1163
  l_S_t_0_t2: for (int t2 = 0; t2 < 10; t2++) {	// L1169
    ap_uint<17> w1;	// L1170
    w1 = 0;	// L1171
    ap_int<33> v725 = t2;	// L1172
    bool v726 = v725 < 10;	// L1173
    if (v726) {	// L1174
      int32_t v727 = v721[0][t2];	// L1175
      bool v728 = v727;	// L1176
      ap_int<17> v729 = w1;	// L1177
      ap_int<17> v730;
      ap_int<17> v730_tmp = v729;
      v730_tmp[0] = v728;      v730 = v730_tmp;	// L1178
      w1 = v730;	// L1179
      half v731 = v720[0][t2];	// L1180
      uint16_t v732;
      union { half from; uint16_t to;} _converter_v731_to_v732;
      _converter_v731_to_v732.from = v731;
      v732 = _converter_v731_to_v732.to;	// L1181
      ap_int<17> v733 = w1;	// L1182
      ap_int<17> v734;
      ap_int<17> v734_tmp = v733;
      v734_tmp(16, 1) = v732;
      v734 = v734_tmp;	// L1183
      w1 = v734;	// L1184
    }
    ap_int<17> v735 = w1;	// L1186
    v722.write(v735);	// L1187
  }
}

void drv_n_0(
  half v736[1][10],
  int32_t v737[1][10],
  hls::stream< ap_uint<17> >& v738
) {	// L1191
  l_S_t_0_t3: for (int t3 = 0; t3 < 10; t3++) {	// L1197
    ap_uint<17> w2;	// L1198
    w2 = 0;	// L1199
    ap_int<33> v741 = t3;	// L1200
    bool v742 = v741 < 10;	// L1201
    if (v742) {	// L1202
      int32_t v743 = v737[0][t3];	// L1203
      bool v744 = v743;	// L1204
      ap_int<17> v745 = w2;	// L1205
      ap_int<17> v746;
      ap_int<17> v746_tmp = v745;
      v746_tmp[0] = v744;      v746 = v746_tmp;	// L1206
      w2 = v746;	// L1207
      half v747 = v736[0][t3];	// L1208
      uint16_t v748;
      union { half from; uint16_t to;} _converter_v747_to_v748;
      _converter_v747_to_v748.from = v747;
      v748 = _converter_v747_to_v748.to;	// L1209
      ap_int<17> v749 = w2;	// L1210
      ap_int<17> v750;
      ap_int<17> v750_tmp = v749;
      v750_tmp(16, 1) = v748;
      v750 = v750_tmp;	// L1211
      w2 = v750;	// L1212
    }
    ap_int<17> v751 = w2;	// L1214
    v738.write(v751);	// L1215
  }
}

void drv_s_0(
  half v752[1][10],
  int32_t v753[1][10],
  hls::stream< ap_uint<17> >& v754
) {	// L1219
  l_S_t_0_t4: for (int t4 = 0; t4 < 10; t4++) {	// L1225
    ap_uint<17> w3;	// L1226
    w3 = 0;	// L1227
    ap_int<33> v757 = t4;	// L1228
    bool v758 = v757 < 10;	// L1229
    if (v758) {	// L1230
      int32_t v759 = v753[0][t4];	// L1231
      bool v760 = v759;	// L1232
      ap_int<17> v761 = w3;	// L1233
      ap_int<17> v762;
      ap_int<17> v762_tmp = v761;
      v762_tmp[0] = v760;      v762 = v762_tmp;	// L1234
      w3 = v762;	// L1235
      half v763 = v752[0][t4];	// L1236
      uint16_t v764;
      union { half from; uint16_t to;} _converter_v763_to_v764;
      _converter_v763_to_v764.from = v763;
      v764 = _converter_v763_to_v764.to;	// L1237
      ap_int<17> v765 = w3;	// L1238
      ap_int<17> v766;
      ap_int<17> v766_tmp = v765;
      v766_tmp(16, 1) = v764;
      v766 = v766_tmp;	// L1239
      w3 = v766;	// L1240
    }
    ap_int<17> v767 = w3;	// L1242
    v754.write(v767);	// L1243
  }
}

void col_w_0(
  half v768[1][10],
  hls::stream< ap_uint<17> >& v769
) {	// L1247
  int32_t k[1];	// L1255
  for (int v771 = 0; v771 < 1; v771++) {	// L1256
    k[v771] = 0;	// L1256
  }
  l_S_t_0_t5: for (int t5 = 0; t5 < 10; t5++) {	// L1257
    ap_uint<17> v773 = v769.read();	// L1258
    ap_uint<17> w4;	// L1259
    w4 = v773;	// L1260
    ap_int<17> v775 = w4;	// L1261
    bool v776;
    ap_int<17> v776_tmp = v775;
    v776 = v776_tmp[0];	// L1262
    int32_t v777 = v776;	// L1263
    bool v778 = v777 == 1;	// L1264
    int32_t v779 = k[0];	// L1265
    bool v780 = v779 < 10;	// L1266
    bool v781 = v778 & v780;	// L1267
    if (v781) {	// L1268
      ap_int<17> v782 = w4;	// L1269
      int16_t v783;
      ap_int<17> v783_tmp = v782;
      v783 = v783_tmp(16, 1);	// L1270
      half v784;
      union { uint16_t from; half to;} _converter_v783_to_v784;
      _converter_v783_to_v784.from = v783;
      v784 = _converter_v783_to_v784.to;	// L1271
      int32_t v785 = k[0];	// L1272
      int v786 = v785;	// L1273
      v768[0][v786] = v784;	// L1274
      int32_t v787 = k[0];	// L1275
      ap_int<33> v788 = v787;	// L1276
      ap_int<33> v789 = v788 + 1;	// L1277
      int32_t v790 = v789;	// L1278
      k[0] = v790;	// L1279
    }
  }
}

void col_e_0(
  half v791[1][10],
  hls::stream< ap_uint<17> >& v792
) {	// L1284
  int32_t k1[1];	// L1292
  for (int v794 = 0; v794 < 1; v794++) {	// L1293
    k1[v794] = 0;	// L1293
  }
  l_S_t_0_t6: for (int t6 = 0; t6 < 10; t6++) {	// L1294
    ap_uint<17> v796 = v792.read();	// L1295
    ap_uint<17> w5;	// L1296
    w5 = v796;	// L1297
    ap_int<17> v798 = w5;	// L1298
    bool v799;
    ap_int<17> v799_tmp = v798;
    v799 = v799_tmp[0];	// L1299
    int32_t v800 = v799;	// L1300
    bool v801 = v800 == 1;	// L1301
    int32_t v802 = k1[0];	// L1302
    bool v803 = v802 < 10;	// L1303
    bool v804 = v801 & v803;	// L1304
    if (v804) {	// L1305
      ap_int<17> v805 = w5;	// L1306
      int16_t v806;
      ap_int<17> v806_tmp = v805;
      v806 = v806_tmp(16, 1);	// L1307
      half v807;
      union { uint16_t from; half to;} _converter_v806_to_v807;
      _converter_v806_to_v807.from = v806;
      v807 = _converter_v806_to_v807.to;	// L1308
      int32_t v808 = k1[0];	// L1309
      int v809 = v808;	// L1310
      v791[0][v809] = v807;	// L1311
      int32_t v810 = k1[0];	// L1312
      ap_int<33> v811 = v810;	// L1313
      ap_int<33> v812 = v811 + 1;	// L1314
      int32_t v813 = v812;	// L1315
      k1[0] = v813;	// L1316
    }
  }
}

void col_n_0(
  half v814[1][10],
  hls::stream< ap_uint<17> >& v815
) {	// L1321
  int32_t k2[1];	// L1329
  for (int v817 = 0; v817 < 1; v817++) {	// L1330
    k2[v817] = 0;	// L1330
  }
  l_S_t_0_t7: for (int t7 = 0; t7 < 10; t7++) {	// L1331
    ap_uint<17> v819 = v815.read();	// L1332
    ap_uint<17> w6;	// L1333
    w6 = v819;	// L1334
    ap_int<17> v821 = w6;	// L1335
    bool v822;
    ap_int<17> v822_tmp = v821;
    v822 = v822_tmp[0];	// L1336
    int32_t v823 = v822;	// L1337
    bool v824 = v823 == 1;	// L1338
    int32_t v825 = k2[0];	// L1339
    bool v826 = v825 < 10;	// L1340
    bool v827 = v824 & v826;	// L1341
    if (v827) {	// L1342
      ap_int<17> v828 = w6;	// L1343
      int16_t v829;
      ap_int<17> v829_tmp = v828;
      v829 = v829_tmp(16, 1);	// L1344
      half v830;
      union { uint16_t from; half to;} _converter_v829_to_v830;
      _converter_v829_to_v830.from = v829;
      v830 = _converter_v829_to_v830.to;	// L1345
      int32_t v831 = k2[0];	// L1346
      int v832 = v831;	// L1347
      v814[0][v832] = v830;	// L1348
      int32_t v833 = k2[0];	// L1349
      ap_int<33> v834 = v833;	// L1350
      ap_int<33> v835 = v834 + 1;	// L1351
      int32_t v836 = v835;	// L1352
      k2[0] = v836;	// L1353
    }
  }
}

void col_s_0(
  half v837[1][10],
  hls::stream< ap_uint<17> >& v838
) {	// L1358
  int32_t k3[1];	// L1366
  for (int v840 = 0; v840 < 1; v840++) {	// L1367
    k3[v840] = 0;	// L1367
  }
  l_S_t_0_t8: for (int t8 = 0; t8 < 10; t8++) {	// L1368
    ap_uint<17> v842 = v838.read();	// L1369
    ap_uint<17> w7;	// L1370
    w7 = v842;	// L1371
    ap_int<17> v844 = w7;	// L1372
    bool v845;
    ap_int<17> v845_tmp = v844;
    v845 = v845_tmp[0];	// L1373
    int32_t v846 = v845;	// L1374
    bool v847 = v846 == 1;	// L1375
    int32_t v848 = k3[0];	// L1376
    bool v849 = v848 < 10;	// L1377
    bool v850 = v847 & v849;	// L1378
    if (v850) {	// L1379
      ap_int<17> v851 = w7;	// L1380
      int16_t v852;
      ap_int<17> v852_tmp = v851;
      v852 = v852_tmp(16, 1);	// L1381
      half v853;
      union { uint16_t from; half to;} _converter_v852_to_v853;
      _converter_v852_to_v853.from = v852;
      v853 = _converter_v852_to_v853.to;	// L1382
      int32_t v854 = k3[0];	// L1383
      int v855 = v854;	// L1384
      v837[0][v855] = v853;	// L1385
      int32_t v856 = k3[0];	// L1386
      ap_int<33> v857 = v856;	// L1387
      ap_int<33> v858 = v857 + 1;	// L1388
      int32_t v859 = v858;	// L1389
      k3[0] = v859;	// L1390
    }
  }
}

void rdrv_w_0(
  int32_t v860[1][10],
  hls::stream< int32_t >& v861,
  hls::stream< ap_uint<26> >& v862
) {	// L1395
  int32_t dcred[1];	// L1402
  for (int v864 = 0; v864 < 1; v864++) {	// L1403
    dcred[v864] = 0;	// L1403
  }
  int32_t sp[1];	// L1404
  for (int v866 = 0; v866 < 1; v866++) {	// L1405
    sp[v866] = 0;	// L1405
  }
  l_S_t_0_t9: for (int t9 = 0; t9 < 10; t9++) {	// L1406
    int32_t v868 = v861.read();	// L1407
    int32_t v869 = dcred[0];	// L1408
    ap_int<33> v870 = v869;	// L1409
    ap_int<33> v871 = v868;	// L1410
    ap_int<33> v872 = v870 + v871;	// L1411
    int32_t v873 = v872;	// L1412
    dcred[0] = v873;	// L1413
    ap_uint<26> pw;	// L1414
    pw = 0;	// L1415
    int32_t v875 = sp[0];	// L1416
    bool v876 = v875 < 10;	// L1417
    if (v876) {	// L1418
      ap_uint<26> cand;	// L1419
      cand = 0;	// L1420
      int32_t v878 = sp[0];	// L1421
      int v879 = v878;	// L1422
      int32_t v880 = v860[0][v879];	// L1423
      ap_uint<26> v881 = v880;	// L1424
      ap_int<26> v882 = cand;	// L1425
      ap_int<26> v883;
      ap_int<26> v883_tmp = v882;
      v883_tmp(25, 0) = v881;
      v883 = v883_tmp;	// L1426
      cand = v883;	// L1427
      ap_int<26> v884 = cand;	// L1428
      bool v885;
      ap_int<26> v885_tmp = v884;
      v885 = v885_tmp[25];	// L1429
      int32_t v886 = v885;	// L1430
      bool v887 = v886 == 0;	// L1431
      if (v887) {	// L1432
        int32_t v888 = sp[0];	// L1433
        ap_int<33> v889 = v888;	// L1434
        ap_int<33> v890 = v889 + 1;	// L1435
        int32_t v891 = v890;	// L1436
        sp[0] = v891;	// L1437
      } else {
        int32_t v892 = dcred[0];	// L1439
        bool v893 = v892 > 0;	// L1440
        if (v893) {	// L1441
          ap_int<26> v894 = cand;	// L1442
          pw = v894;	// L1443
          int32_t v895 = dcred[0];	// L1444
          ap_int<33> v896 = v895;	// L1445
          ap_int<33> v897 = v896 - 1;	// L1446
          int32_t v898 = v897;	// L1447
          dcred[0] = v898;	// L1448
          int32_t v899 = sp[0];	// L1449
          ap_int<33> v900 = v899;	// L1450
          ap_int<33> v901 = v900 + 1;	// L1451
          int32_t v902 = v901;	// L1452
          sp[0] = v902;	// L1453
        }
      }
    }
    ap_int<26> v903 = pw;	// L1457
    v862.write(v903);	// L1458
  }
}

void rdrv_e_0(
  int32_t v904[1][10],
  hls::stream< int32_t >& v905,
  hls::stream< ap_uint<26> >& v906
) {	// L1462
  int32_t dcred1[1];	// L1469
  for (int v908 = 0; v908 < 1; v908++) {	// L1470
    dcred1[v908] = 0;	// L1470
  }
  int32_t sp1[1];	// L1471
  for (int v910 = 0; v910 < 1; v910++) {	// L1472
    sp1[v910] = 0;	// L1472
  }
  l_S_t_0_t10: for (int t10 = 0; t10 < 10; t10++) {	// L1473
    int32_t v912 = v905.read();	// L1474
    int32_t v913 = dcred1[0];	// L1475
    ap_int<33> v914 = v913;	// L1476
    ap_int<33> v915 = v912;	// L1477
    ap_int<33> v916 = v914 + v915;	// L1478
    int32_t v917 = v916;	// L1479
    dcred1[0] = v917;	// L1480
    ap_uint<26> pw1;	// L1481
    pw1 = 0;	// L1482
    int32_t v919 = sp1[0];	// L1483
    bool v920 = v919 < 10;	// L1484
    if (v920) {	// L1485
      ap_uint<26> cand1;	// L1486
      cand1 = 0;	// L1487
      int32_t v922 = sp1[0];	// L1488
      int v923 = v922;	// L1489
      int32_t v924 = v904[0][v923];	// L1490
      ap_uint<26> v925 = v924;	// L1491
      ap_int<26> v926 = cand1;	// L1492
      ap_int<26> v927;
      ap_int<26> v927_tmp = v926;
      v927_tmp(25, 0) = v925;
      v927 = v927_tmp;	// L1493
      cand1 = v927;	// L1494
      ap_int<26> v928 = cand1;	// L1495
      bool v929;
      ap_int<26> v929_tmp = v928;
      v929 = v929_tmp[25];	// L1496
      int32_t v930 = v929;	// L1497
      bool v931 = v930 == 0;	// L1498
      if (v931) {	// L1499
        int32_t v932 = sp1[0];	// L1500
        ap_int<33> v933 = v932;	// L1501
        ap_int<33> v934 = v933 + 1;	// L1502
        int32_t v935 = v934;	// L1503
        sp1[0] = v935;	// L1504
      } else {
        int32_t v936 = dcred1[0];	// L1506
        bool v937 = v936 > 0;	// L1507
        if (v937) {	// L1508
          ap_int<26> v938 = cand1;	// L1509
          pw1 = v938;	// L1510
          int32_t v939 = dcred1[0];	// L1511
          ap_int<33> v940 = v939;	// L1512
          ap_int<33> v941 = v940 - 1;	// L1513
          int32_t v942 = v941;	// L1514
          dcred1[0] = v942;	// L1515
          int32_t v943 = sp1[0];	// L1516
          ap_int<33> v944 = v943;	// L1517
          ap_int<33> v945 = v944 + 1;	// L1518
          int32_t v946 = v945;	// L1519
          sp1[0] = v946;	// L1520
        }
      }
    }
    ap_int<26> v947 = pw1;	// L1524
    v906.write(v947);	// L1525
  }
}

void rdrv_n_0(
  int32_t v948[1][10],
  hls::stream< int32_t >& v949,
  hls::stream< ap_uint<26> >& v950
) {	// L1529
  int32_t dcred2[1];	// L1536
  for (int v952 = 0; v952 < 1; v952++) {	// L1537
    dcred2[v952] = 0;	// L1537
  }
  int32_t sp2[1];	// L1538
  for (int v954 = 0; v954 < 1; v954++) {	// L1539
    sp2[v954] = 0;	// L1539
  }
  l_S_t_0_t11: for (int t11 = 0; t11 < 10; t11++) {	// L1540
    int32_t v956 = v949.read();	// L1541
    int32_t v957 = dcred2[0];	// L1542
    ap_int<33> v958 = v957;	// L1543
    ap_int<33> v959 = v956;	// L1544
    ap_int<33> v960 = v958 + v959;	// L1545
    int32_t v961 = v960;	// L1546
    dcred2[0] = v961;	// L1547
    ap_uint<26> pw2;	// L1548
    pw2 = 0;	// L1549
    int32_t v963 = sp2[0];	// L1550
    bool v964 = v963 < 10;	// L1551
    if (v964) {	// L1552
      ap_uint<26> cand2;	// L1553
      cand2 = 0;	// L1554
      int32_t v966 = sp2[0];	// L1555
      int v967 = v966;	// L1556
      int32_t v968 = v948[0][v967];	// L1557
      ap_uint<26> v969 = v968;	// L1558
      ap_int<26> v970 = cand2;	// L1559
      ap_int<26> v971;
      ap_int<26> v971_tmp = v970;
      v971_tmp(25, 0) = v969;
      v971 = v971_tmp;	// L1560
      cand2 = v971;	// L1561
      ap_int<26> v972 = cand2;	// L1562
      bool v973;
      ap_int<26> v973_tmp = v972;
      v973 = v973_tmp[25];	// L1563
      int32_t v974 = v973;	// L1564
      bool v975 = v974 == 0;	// L1565
      if (v975) {	// L1566
        int32_t v976 = sp2[0];	// L1567
        ap_int<33> v977 = v976;	// L1568
        ap_int<33> v978 = v977 + 1;	// L1569
        int32_t v979 = v978;	// L1570
        sp2[0] = v979;	// L1571
      } else {
        int32_t v980 = dcred2[0];	// L1573
        bool v981 = v980 > 0;	// L1574
        if (v981) {	// L1575
          ap_int<26> v982 = cand2;	// L1576
          pw2 = v982;	// L1577
          int32_t v983 = dcred2[0];	// L1578
          ap_int<33> v984 = v983;	// L1579
          ap_int<33> v985 = v984 - 1;	// L1580
          int32_t v986 = v985;	// L1581
          dcred2[0] = v986;	// L1582
          int32_t v987 = sp2[0];	// L1583
          ap_int<33> v988 = v987;	// L1584
          ap_int<33> v989 = v988 + 1;	// L1585
          int32_t v990 = v989;	// L1586
          sp2[0] = v990;	// L1587
        }
      }
    }
    ap_int<26> v991 = pw2;	// L1591
    v950.write(v991);	// L1592
  }
}

void rdrv_s_0(
  int32_t v992[1][10],
  hls::stream< int32_t >& v993,
  hls::stream< ap_uint<26> >& v994
) {	// L1596
  int32_t dcred3[1];	// L1603
  for (int v996 = 0; v996 < 1; v996++) {	// L1604
    dcred3[v996] = 0;	// L1604
  }
  int32_t sp3[1];	// L1605
  for (int v998 = 0; v998 < 1; v998++) {	// L1606
    sp3[v998] = 0;	// L1606
  }
  l_S_t_0_t12: for (int t12 = 0; t12 < 10; t12++) {	// L1607
    int32_t v1000 = v993.read();	// L1608
    int32_t v1001 = dcred3[0];	// L1609
    ap_int<33> v1002 = v1001;	// L1610
    ap_int<33> v1003 = v1000;	// L1611
    ap_int<33> v1004 = v1002 + v1003;	// L1612
    int32_t v1005 = v1004;	// L1613
    dcred3[0] = v1005;	// L1614
    ap_uint<26> pw3;	// L1615
    pw3 = 0;	// L1616
    int32_t v1007 = sp3[0];	// L1617
    bool v1008 = v1007 < 10;	// L1618
    if (v1008) {	// L1619
      ap_uint<26> cand3;	// L1620
      cand3 = 0;	// L1621
      int32_t v1010 = sp3[0];	// L1622
      int v1011 = v1010;	// L1623
      int32_t v1012 = v992[0][v1011];	// L1624
      ap_uint<26> v1013 = v1012;	// L1625
      ap_int<26> v1014 = cand3;	// L1626
      ap_int<26> v1015;
      ap_int<26> v1015_tmp = v1014;
      v1015_tmp(25, 0) = v1013;
      v1015 = v1015_tmp;	// L1627
      cand3 = v1015;	// L1628
      ap_int<26> v1016 = cand3;	// L1629
      bool v1017;
      ap_int<26> v1017_tmp = v1016;
      v1017 = v1017_tmp[25];	// L1630
      int32_t v1018 = v1017;	// L1631
      bool v1019 = v1018 == 0;	// L1632
      if (v1019) {	// L1633
        int32_t v1020 = sp3[0];	// L1634
        ap_int<33> v1021 = v1020;	// L1635
        ap_int<33> v1022 = v1021 + 1;	// L1636
        int32_t v1023 = v1022;	// L1637
        sp3[0] = v1023;	// L1638
      } else {
        int32_t v1024 = dcred3[0];	// L1640
        bool v1025 = v1024 > 0;	// L1641
        if (v1025) {	// L1642
          ap_int<26> v1026 = cand3;	// L1643
          pw3 = v1026;	// L1644
          int32_t v1027 = dcred3[0];	// L1645
          ap_int<33> v1028 = v1027;	// L1646
          ap_int<33> v1029 = v1028 - 1;	// L1647
          int32_t v1030 = v1029;	// L1648
          dcred3[0] = v1030;	// L1649
          int32_t v1031 = sp3[0];	// L1650
          ap_int<33> v1032 = v1031;	// L1651
          ap_int<33> v1033 = v1032 + 1;	// L1652
          int32_t v1034 = v1033;	// L1653
          sp3[0] = v1034;	// L1654
        }
      }
    }
    ap_int<26> v1035 = pw3;	// L1658
    v994.write(v1035);	// L1659
  }
}

void rclc_w_0(
  int32_t v1036[1][10],
  hls::stream< int32_t >& v1037,
  hls::stream< ap_uint<26> >& v1038
) {	// L1663
  int32_t k4[1];	// L1672
  for (int v1040 = 0; v1040 < 1; v1040++) {	// L1673
    k4[v1040] = 0;	// L1673
  }
  int32_t cret[1];	// L1674
  for (int v1042 = 0; v1042 < 1; v1042++) {	// L1675
    cret[v1042] = 0;	// L1675
  }
  cret[0] = 2;	// L1676
  int32_t v1043 = cret[0];	// L1677
  v1037.write(v1043);	// L1678
  l_S_t_0_t13: for (int t13 = 0; t13 < 10; t13++) {	// L1679
    ap_uint<26> v1045 = v1038.read();	// L1680
    ap_uint<26> pw4;	// L1681
    pw4 = v1045;	// L1682
    cret[0] = 0;	// L1683
    ap_int<26> v1047 = pw4;	// L1684
    bool v1048;
    ap_int<26> v1048_tmp = v1047;
    v1048 = v1048_tmp[25];	// L1685
    int32_t v1049 = v1048;	// L1686
    bool v1050 = v1049 == 1;	// L1687
    if (v1050) {	// L1688
      cret[0] = 1;	// L1689
      int32_t v1051 = k4[0];	// L1690
      bool v1052 = v1051 < 10;	// L1691
      if (v1052) {	// L1692
        ap_int<26> v1053 = pw4;	// L1693
        int32_t v1054 = v1053;	// L1694
        int32_t v1055 = v1054 & 67108863;	// L1695
        int32_t v1056 = k4[0];	// L1696
        int v1057 = v1056;	// L1697
        v1036[0][v1057] = v1055;	// L1698
        int32_t v1058 = k4[0];	// L1699
        ap_int<33> v1059 = v1058;	// L1700
        ap_int<33> v1060 = v1059 + 1;	// L1701
        int32_t v1061 = v1060;	// L1702
        k4[0] = v1061;	// L1703
      }
    }
    int32_t v1062 = cret[0];	// L1706
    v1037.write(v1062);	// L1707
  }
}

void rclc_e_0(
  int32_t v1063[1][10],
  hls::stream< int32_t >& v1064,
  hls::stream< ap_uint<26> >& v1065
) {	// L1711
  int32_t k5[1];	// L1720
  for (int v1067 = 0; v1067 < 1; v1067++) {	// L1721
    k5[v1067] = 0;	// L1721
  }
  int32_t cret1[1];	// L1722
  for (int v1069 = 0; v1069 < 1; v1069++) {	// L1723
    cret1[v1069] = 0;	// L1723
  }
  cret1[0] = 2;	// L1724
  int32_t v1070 = cret1[0];	// L1725
  v1064.write(v1070);	// L1726
  l_S_t_0_t14: for (int t14 = 0; t14 < 10; t14++) {	// L1727
    ap_uint<26> v1072 = v1065.read();	// L1728
    ap_uint<26> pw5;	// L1729
    pw5 = v1072;	// L1730
    cret1[0] = 0;	// L1731
    ap_int<26> v1074 = pw5;	// L1732
    bool v1075;
    ap_int<26> v1075_tmp = v1074;
    v1075 = v1075_tmp[25];	// L1733
    int32_t v1076 = v1075;	// L1734
    bool v1077 = v1076 == 1;	// L1735
    if (v1077) {	// L1736
      cret1[0] = 1;	// L1737
      int32_t v1078 = k5[0];	// L1738
      bool v1079 = v1078 < 10;	// L1739
      if (v1079) {	// L1740
        ap_int<26> v1080 = pw5;	// L1741
        int32_t v1081 = v1080;	// L1742
        int32_t v1082 = v1081 & 67108863;	// L1743
        int32_t v1083 = k5[0];	// L1744
        int v1084 = v1083;	// L1745
        v1063[0][v1084] = v1082;	// L1746
        int32_t v1085 = k5[0];	// L1747
        ap_int<33> v1086 = v1085;	// L1748
        ap_int<33> v1087 = v1086 + 1;	// L1749
        int32_t v1088 = v1087;	// L1750
        k5[0] = v1088;	// L1751
      }
    }
    int32_t v1089 = cret1[0];	// L1754
    v1064.write(v1089);	// L1755
  }
}

void rclc_n_0(
  int32_t v1090[1][10],
  hls::stream< int32_t >& v1091,
  hls::stream< ap_uint<26> >& v1092
) {	// L1759
  int32_t k6[1];	// L1768
  for (int v1094 = 0; v1094 < 1; v1094++) {	// L1769
    k6[v1094] = 0;	// L1769
  }
  int32_t cret2[1];	// L1770
  for (int v1096 = 0; v1096 < 1; v1096++) {	// L1771
    cret2[v1096] = 0;	// L1771
  }
  cret2[0] = 2;	// L1772
  int32_t v1097 = cret2[0];	// L1773
  v1091.write(v1097);	// L1774
  l_S_t_0_t15: for (int t15 = 0; t15 < 10; t15++) {	// L1775
    ap_uint<26> v1099 = v1092.read();	// L1776
    ap_uint<26> pw6;	// L1777
    pw6 = v1099;	// L1778
    cret2[0] = 0;	// L1779
    ap_int<26> v1101 = pw6;	// L1780
    bool v1102;
    ap_int<26> v1102_tmp = v1101;
    v1102 = v1102_tmp[25];	// L1781
    int32_t v1103 = v1102;	// L1782
    bool v1104 = v1103 == 1;	// L1783
    if (v1104) {	// L1784
      cret2[0] = 1;	// L1785
      int32_t v1105 = k6[0];	// L1786
      bool v1106 = v1105 < 10;	// L1787
      if (v1106) {	// L1788
        ap_int<26> v1107 = pw6;	// L1789
        int32_t v1108 = v1107;	// L1790
        int32_t v1109 = v1108 & 67108863;	// L1791
        int32_t v1110 = k6[0];	// L1792
        int v1111 = v1110;	// L1793
        v1090[0][v1111] = v1109;	// L1794
        int32_t v1112 = k6[0];	// L1795
        ap_int<33> v1113 = v1112;	// L1796
        ap_int<33> v1114 = v1113 + 1;	// L1797
        int32_t v1115 = v1114;	// L1798
        k6[0] = v1115;	// L1799
      }
    }
    int32_t v1116 = cret2[0];	// L1802
    v1091.write(v1116);	// L1803
  }
}

void rclc_s_0(
  int32_t v1117[1][10],
  hls::stream< int32_t >& v1118,
  hls::stream< ap_uint<26> >& v1119
) {	// L1807
  int32_t k7[1];	// L1816
  for (int v1121 = 0; v1121 < 1; v1121++) {	// L1817
    k7[v1121] = 0;	// L1817
  }
  int32_t cret3[1];	// L1818
  for (int v1123 = 0; v1123 < 1; v1123++) {	// L1819
    cret3[v1123] = 0;	// L1819
  }
  cret3[0] = 2;	// L1820
  int32_t v1124 = cret3[0];	// L1821
  v1118.write(v1124);	// L1822
  l_S_t_0_t16: for (int t16 = 0; t16 < 10; t16++) {	// L1823
    ap_uint<26> v1126 = v1119.read();	// L1824
    ap_uint<26> pw7;	// L1825
    pw7 = v1126;	// L1826
    cret3[0] = 0;	// L1827
    ap_int<26> v1128 = pw7;	// L1828
    bool v1129;
    ap_int<26> v1129_tmp = v1128;
    v1129 = v1129_tmp[25];	// L1829
    int32_t v1130 = v1129;	// L1830
    bool v1131 = v1130 == 1;	// L1831
    if (v1131) {	// L1832
      cret3[0] = 1;	// L1833
      int32_t v1132 = k7[0];	// L1834
      bool v1133 = v1132 < 10;	// L1835
      if (v1133) {	// L1836
        ap_int<26> v1134 = pw7;	// L1837
        int32_t v1135 = v1134;	// L1838
        int32_t v1136 = v1135 & 67108863;	// L1839
        int32_t v1137 = k7[0];	// L1840
        int v1138 = v1137;	// L1841
        v1117[0][v1138] = v1136;	// L1842
        int32_t v1139 = k7[0];	// L1843
        ap_int<33> v1140 = v1139;	// L1844
        ap_int<33> v1141 = v1140 + 1;	// L1845
        int32_t v1142 = v1141;	// L1846
        k7[0] = v1142;	// L1847
      }
    }
    int32_t v1143 = cret3[0];	// L1850
    v1118.write(v1143);	// L1851
  }
}

/// This is top function.
void top(
  half v1144[1][10],
  int32_t v1145[1][10],
  half v1146[1][10],
  int32_t v1147[1][10],
  half v1148[1][10],
  int32_t v1149[1][10],
  half v1150[1][10],
  int32_t v1151[1][10],
  half v1152[1][10],
  half v1153[1][10],
  half v1154[1][10],
  half v1155[1][10],
  int32_t v1156[1][10],
  int32_t v1157[1][10],
  int32_t v1158[1][10],
  int32_t v1159[1][10],
  int32_t v1160[1][10],
  int32_t v1161[1][10],
  int32_t v1162[1][10],
  int32_t v1163[1][10]
) {	// L1855
  #pragma HLS dataflow
  hls::stream< ap_uint<17> > v1164;
  #pragma HLS stream variable=v1164 depth=2	// L1856
  hls::stream< ap_uint<17> > v1165;
  #pragma HLS stream variable=v1165 depth=2	// L1857
  hls::stream< ap_uint<17> > v1166;
  #pragma HLS stream variable=v1166 depth=2	// L1858
  hls::stream< ap_uint<17> > v1167;
  #pragma HLS stream variable=v1167 depth=2	// L1859
  hls::stream< ap_uint<17> > v1168;
  #pragma HLS stream variable=v1168 depth=2	// L1860
  hls::stream< ap_uint<17> > v1169;
  #pragma HLS stream variable=v1169 depth=2	// L1861
  hls::stream< ap_uint<17> > v1170;
  #pragma HLS stream variable=v1170 depth=2	// L1862
  hls::stream< ap_uint<17> > v1171;
  #pragma HLS stream variable=v1171 depth=2	// L1863
  hls::stream< ap_uint<26> > v1172;
  #pragma HLS stream variable=v1172 depth=2	// L1864
  hls::stream< ap_uint<26> > v1173;
  #pragma HLS stream variable=v1173 depth=2	// L1865
  hls::stream< ap_uint<26> > v1174;
  #pragma HLS stream variable=v1174 depth=2	// L1866
  hls::stream< ap_uint<26> > v1175;
  #pragma HLS stream variable=v1175 depth=2	// L1867
  hls::stream< ap_uint<26> > v1176;
  #pragma HLS stream variable=v1176 depth=2	// L1868
  hls::stream< ap_uint<26> > v1177;
  #pragma HLS stream variable=v1177 depth=2	// L1869
  hls::stream< ap_uint<26> > v1178;
  #pragma HLS stream variable=v1178 depth=2	// L1870
  hls::stream< ap_uint<26> > v1179;
  #pragma HLS stream variable=v1179 depth=2	// L1871
  hls::stream< int32_t > v1180;
  #pragma HLS stream variable=v1180 depth=2	// L1872
  hls::stream< int32_t > v1181;
  #pragma HLS stream variable=v1181 depth=2	// L1873
  hls::stream< int32_t > v1182;
  #pragma HLS stream variable=v1182 depth=2	// L1874
  hls::stream< int32_t > v1183;
  #pragma HLS stream variable=v1183 depth=2	// L1875
  hls::stream< int32_t > v1184;
  #pragma HLS stream variable=v1184 depth=2	// L1876
  hls::stream< int32_t > v1185;
  #pragma HLS stream variable=v1185 depth=2	// L1877
  hls::stream< int32_t > v1186;
  #pragma HLS stream variable=v1186 depth=2	// L1878
  hls::stream< int32_t > v1187;
  #pragma HLS stream variable=v1187 depth=2	// L1879
  node_0_0(v1173, v1174, v1177, v1178, v1165, v1166, v1169, v1170, v1180, v1183, v1184, v1187, v1172, v1175, v1176, v1179, v1181, v1182, v1185, v1186, v1164, v1167, v1168, v1171);	// L1880
  drv_w_0(v1144, v1145, v1164);	// L1881
  drv_e_0(v1146, v1147, v1167);	// L1882
  drv_n_0(v1148, v1149, v1168);	// L1883
  drv_s_0(v1150, v1151, v1171);	// L1884
  col_w_0(v1152, v1166);	// L1885
  col_e_0(v1153, v1165);	// L1886
  col_n_0(v1154, v1170);	// L1887
  col_s_0(v1155, v1169);	// L1888
  rdrv_w_0(v1156, v1180, v1172);	// L1889
  rdrv_e_0(v1157, v1183, v1175);	// L1890
  rdrv_n_0(v1158, v1184, v1176);	// L1891
  rdrv_s_0(v1159, v1187, v1179);	// L1892
  rclc_w_0(v1160, v1182, v1174);	// L1893
  rclc_e_0(v1161, v1181, v1173);	// L1894
  rclc_n_0(v1162, v1186, v1178);	// L1895
  rclc_s_0(v1163, v1185, v1177);	// L1896
}

