
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
) {	// L4
  int32_t irf[8];	// L35
  #pragma HLS array_partition variable=irf complete dim=1

  for (int v25 = 0; v25 < 8; v25++) {	// L36
    irf[v25] = 0;	// L36
  }
  half drf[8];	// L37
  #pragma HLS array_partition variable=drf complete dim=1

  for (int v27 = 0; v27 < 8; v27++) {	// L38
    drf[v27] = (double)0.000000;	// L38
  }
  int32_t drf_full[8];	// L39
  #pragma HLS array_partition variable=drf_full complete dim=1

  for (int v29 = 0; v29 < 8; v29++) {	// L40
    drf_full[v29] = 0;	// L40
  }
  int32_t dsmask;	// L41
  dsmask = 0;	// L42
  int32_t crv_vld;	// L43
  crv_vld = 0;	// L44
  half crv_data;	// L45
  crv_data = (double)0.000000;	// L46
  int32_t crv_addr;	// L47
  crv_addr = 0;	// L48
  int32_t crv_mode;	// L49
  crv_mode = 0;	// L50
  int32_t crv_raw;	// L51
  crv_raw = 0;	// L52
  int32_t csd_vld;	// L53
  csd_vld = 0;	// L54
  ap_uint<26> csd_pkt;	// L55
  csd_pkt = 0;	// L56
  int32_t csd_dir;	// L57
  csd_dir = 0;	// L58
  int32_t row_id;	// L59
  row_id = 0;	// L60
  int32_t col_id;	// L61
  col_id = 0;	// L62
  ap_uint<26> oe_r;	// L63
  oe_r = 0;	// L64
  ap_uint<26> ow_r;	// L65
  ow_r = 0;	// L66
  ap_uint<26> on_r;	// L67
  on_r = 0;	// L68
  ap_uint<26> os_r;	// L69
  os_r = 0;	// L70
  ap_uint<17> txn_r;	// L71
  txn_r = 0;	// L72
  ap_uint<17> txs_r;	// L73
  txs_r = 0;	// L74
  ap_uint<17> txw_r;	// L75
  txw_r = 0;	// L76
  ap_uint<17> txe_r;	// L77
  txe_r = 0;	// L78
  half hold_v[4][2];	// L79
  #pragma HLS array_partition variable=hold_v complete dim=1
  #pragma HLS array_partition variable=hold_v complete dim=2

  for (int v50 = 0; v50 < 4; v50++) {	// L80
    for (int v51 = 0; v51 < 2; v51++) {	// L80
      hold_v[v50][v51] = (double)0.000000;	// L80
    }
  }
  int32_t hold_cnt[4];	// L81
  #pragma HLS array_partition variable=hold_cnt complete dim=1

  for (int v53 = 0; v53 < 4; v53++) {	// L82
    hold_cnt[v53] = 0;	// L82
  }
  ap_uint<26> rbuf[4][2];	// L83
  #pragma HLS array_partition variable=rbuf complete dim=1
  #pragma HLS array_partition variable=rbuf complete dim=2

  for (int v55 = 0; v55 < 4; v55++) {	// L84
    for (int v56 = 0; v56 < 2; v56++) {	// L84
      rbuf[v55][v56] = 0;	// L84
    }
  }
  int32_t rbcnt[4];	// L85
  #pragma HLS array_partition variable=rbcnt complete dim=1

  for (int v58 = 0; v58 < 4; v58++) {	// L86
    rbcnt[v58] = 0;	// L86
  }
  int32_t rcred[4];	// L87
  #pragma HLS array_partition variable=rcred complete dim=1

  for (int v60 = 0; v60 < 4; v60++) {	// L88
    rcred[v60] = 0;	// L88
  }
  int32_t cre_r;	// L89
  cre_r = 2;	// L90
  int32_t crw_r;	// L91
  crw_r = 2;	// L92
  int32_t crs_r;	// L93
  crs_r = 2;	// L94
  int32_t crn_r;	// L95
  crn_r = 2;	// L96
  int32_t cfg_isz;	// L97
  cfg_isz = 0;	// L98
  int32_t cfg_itsz;	// L99
  cfg_itsz = 0;	// L100
  int32_t fetch_en;	// L101
  fetch_en = 0;	// L102
  int32_t instr_cnt;	// L103
  instr_cnt = 0;	// L104
  int32_t iter_cnt;	// L105
  iter_cnt = 0;	// L106
  int32_t condition_reg;	// L107
  condition_reg = 0;	// L108
  ap_int<26> v71 = oe_r;	// L109
  v0.write(v71);	// L110
  ap_int<26> v72 = ow_r;	// L111
  v1.write(v72);	// L112
  ap_int<26> v73 = os_r;	// L113
  v2.write(v73);	// L114
  ap_int<26> v74 = on_r;	// L115
  v3.write(v74);	// L116
  ap_int<17> v75 = txe_r;	// L117
  v4.write(v75);	// L118
  ap_int<17> v76 = txw_r;	// L119
  v5.write(v76);	// L120
  ap_int<17> v77 = txs_r;	// L121
  v6.write(v77);	// L122
  ap_int<17> v78 = txn_r;	// L123
  v7.write(v78);	// L124
  int32_t v79 = cre_r;	// L125
  v8.write(v79);	// L126
  int32_t v80 = crw_r;	// L127
  v9.write(v80);	// L128
  int32_t v81 = crs_r;	// L129
  v10.write(v81);	// L130
  int32_t v82 = crn_r;	// L131
  v11.write(v82);	// L132
  l_S_t_0_t: for (int t = 0; t < 10; t++) {	// L133
  #pragma HLS pipeline II=1
    ap_uint<26> v84 = v12.read();	// L134
    ap_uint<26> p_w;	// L135
    p_w = v84;	// L136
    ap_uint<26> v86 = v13.read();	// L137
    ap_uint<26> p_e;	// L138
    p_e = v86;	// L139
    ap_uint<26> v88 = v14.read();	// L140
    ap_uint<26> p_n;	// L141
    p_n = v88;	// L142
    ap_uint<26> v90 = v15.read();	// L143
    ap_uint<26> p_s;	// L144
    p_s = v90;	// L145
    int32_t v92 = v16.read();	// L146
    int32_t v93 = rcred[0];	// L147
    ap_int<33> v94 = v93;	// L148
    ap_int<33> v95 = v92;	// L149
    ap_int<33> v96 = v94 + v95;	// L150
    int32_t v97 = v96;	// L151
    rcred[0] = v97;	// L152
    int32_t v98 = v17.read();	// L153
    int32_t v99 = rcred[1];	// L154
    ap_int<33> v100 = v99;	// L155
    ap_int<33> v101 = v98;	// L156
    ap_int<33> v102 = v100 + v101;	// L157
    int32_t v103 = v102;	// L158
    rcred[1] = v103;	// L159
    int32_t v104 = v18.read();	// L160
    int32_t v105 = rcred[2];	// L161
    ap_int<33> v106 = v105;	// L162
    ap_int<33> v107 = v104;	// L163
    ap_int<33> v108 = v106 + v107;	// L164
    int32_t v109 = v108;	// L165
    rcred[2] = v109;	// L166
    int32_t v110 = v19.read();	// L167
    int32_t v111 = rcred[3];	// L168
    ap_int<33> v112 = v111;	// L169
    ap_int<33> v113 = v110;	// L170
    ap_int<33> v114 = v112 + v113;	// L171
    int32_t v115 = v114;	// L172
    rcred[3] = v115;	// L173
    ap_uint<26> fin[4];	// L174
    for (int v117 = 0; v117 < 4; v117++) {	// L175
      fin[v117] = 0;	// L175
    }
    ap_int<26> v118 = p_w;	// L176
    fin[0] = v118;	// L177
    ap_int<26> v119 = p_e;	// L178
    fin[1] = v119;	// L179
    ap_int<26> v120 = p_n;	// L180
    fin[2] = v120;	// L181
    ap_int<26> v121 = p_s;	// L182
    fin[3] = v121;	// L183
    l_S_d_0_d: for (int d = 0; d < 4; d++) {	// L184
      ap_uint<26> v123 = fin[d];	// L185
      bool v124;
      ap_int<26> v124_tmp = v123;
      v124 = v124_tmp[25];	// L186
      int32_t v125 = v124;	// L187
      bool v126 = v125 == 1;	// L188
      int32_t v127 = rbcnt[d];	// L189
      bool v128 = v127 < 2;	// L190
      bool v129 = v126 & v128;	// L191
      if (v129) {	// L192
        ap_uint<26> v130 = fin[d];	// L193
        int32_t v131 = rbcnt[d];	// L194
        int v132 = v131;	// L195
        rbuf[d][v132] = v130;	// L196
        int32_t v133 = rbcnt[d];	// L197
        ap_int<33> v134 = v133;	// L198
        ap_int<33> v135 = v134 + 1;	// L199
        int32_t v136 = v135;	// L200
        rbcnt[d] = v136;	// L201
      }
    }
    ap_uint<26> hd[4];	// L204
    for (int v138 = 0; v138 < 4; v138++) {	// L205
      hd[v138] = 0;	// L205
    }
    int32_t hvld[4];	// L206
    for (int v140 = 0; v140 < 4; v140++) {	// L207
      hvld[v140] = 0;	// L207
    }
    int32_t hit[4];	// L208
    for (int v142 = 0; v142 < 4; v142++) {	// L209
      hit[v142] = 0;	// L209
    }
    int32_t axis[4];	// L210
    for (int v144 = 0; v144 < 4; v144++) {	// L211
      axis[v144] = 0;	// L211
    }
    int32_t v145 = col_id;	// L212
    axis[0] = v145;	// L213
    int32_t v146 = col_id;	// L214
    axis[1] = v146;	// L215
    int32_t v147 = row_id;	// L216
    axis[2] = v147;	// L217
    int32_t v148 = row_id;	// L218
    axis[3] = v148;	// L219
    l_S_d_1_d1: for (int d1 = 0; d1 < 4; d1++) {	// L220
      int32_t v150 = rbcnt[d1];	// L221
      bool v151 = v150 > 0;	// L222
      if (v151) {	// L223
        ap_uint<26> v152 = rbuf[d1][0];	// L224
        hd[d1] = v152;	// L225
        hvld[d1] = 1;	// L226
        ap_uint<26> v153 = hd[d1];	// L227
        ap_int<4> v154;
        ap_int<26> v154_tmp = v153;
        v154 = v154_tmp(24, 21);	// L228
        int32_t v155 = axis[d1];	// L229
        int32_t v156 = v154;	// L230
        bool v157 = v156 == v155;	// L231
        if (v157) {	// L232
          hit[d1] = 1;	// L233
        }
      }
    }
    ap_uint<26> o_crv;	// L237
    o_crv = 0;	// L238
    int32_t crv_in;	// L239
    crv_in = -1;	// L240
    int32_t v160 = hit[3];	// L241
    bool v161 = v160 == 1;	// L242
    if (v161) {	// L243
      ap_uint<26> v162 = hd[3];	// L244
      o_crv = v162;	// L245
      crv_in = 3;	// L246
    } else {
      int32_t v163 = hit[2];	// L248
      bool v164 = v163 == 1;	// L249
      if (v164) {	// L250
        ap_uint<26> v165 = hd[2];	// L251
        o_crv = v165;	// L252
        crv_in = 2;	// L253
      } else {
        int32_t v166 = hit[1];	// L255
        bool v167 = v166 == 1;	// L256
        if (v167) {	// L257
          ap_uint<26> v168 = hd[1];	// L258
          o_crv = v168;	// L259
          crv_in = 1;	// L260
        } else {
          int32_t v169 = hit[0];	// L262
          bool v170 = v169 == 1;	// L263
          if (v170) {	// L264
            ap_uint<26> v171 = hd[0];	// L265
            o_crv = v171;	// L266
            crv_in = 0;	// L267
          }
        }
      }
    }
    ap_uint<26> o_out[4];	// L272
    for (int v173 = 0; v173 < 4; v173++) {	// L273
      o_out[v173] = 0;	// L273
    }
    int32_t pop[4];	// L274
    for (int v175 = 0; v175 < 4; v175++) {	// L275
      pop[v175] = 0;	// L275
    }
    int32_t inj_done;	// L276
    inj_done = 0;	// L277
    int32_t idir;	// L278
    idir = -1;	// L279
    ap_int<26> v178 = csd_pkt;	// L280
    bool v179;
    ap_int<26> v179_tmp = v178;
    v179 = v179_tmp[25];	// L281
    int32_t v180 = v179;	// L282
    bool v181 = v180 == 1;	// L283
    if (v181) {	// L284
      int32_t v182 = csd_dir;	// L285
      ap_int<33> v183 = v182;	// L286
      ap_int<33> v184 = 3 - v183;	// L287
      int32_t v185 = v184;	// L288
      idir = v185;	// L289
    }
    l_S_o_2_o: for (int o = 0; o < 4; o++) {	// L291
      int32_t v187 = rcred[o];	// L292
      bool v188 = v187 > 0;	// L293
      if (v188) {	// L294
        int32_t v189 = idir;	// L295
        ap_int<33> v190 = v189;	// L296
        ap_int<33> v191 = o;	// L297
        bool v192 = v190 == v191;	// L298
        if (v192) {	// L299
          ap_int<26> v193 = csd_pkt;	// L300
          o_out[o] = v193;	// L301
          int32_t v194 = rcred[o];	// L302
          ap_int<33> v195 = v194;	// L303
          ap_int<33> v196 = v195 - 1;	// L304
          int32_t v197 = v196;	// L305
          rcred[o] = v197;	// L306
          inj_done = 1;	// L307
        } else {
          int32_t v198 = hvld[o];	// L309
          bool v199 = v198 == 1;	// L310
          int32_t v200 = hit[o];	// L311
          bool v201 = v200 == 0;	// L312
          bool v202 = v199 & v201;	// L313
          if (v202) {	// L314
            ap_uint<26> v203 = hd[o];	// L315
            o_out[o] = v203;	// L316
            int32_t v204 = rcred[o];	// L317
            ap_int<33> v205 = v204;	// L318
            ap_int<33> v206 = v205 - 1;	// L319
            int32_t v207 = v206;	// L320
            rcred[o] = v207;	// L321
            pop[o] = 1;	// L322
          }
        }
      }
    }
    int32_t v208 = crv_in;	// L327
    bool v209 = v208 >= 0;	// L328
    if (v209) {	// L329
      int32_t v210 = crv_in;	// L330
      int v211 = v210;	// L331
      pop[v211] = 1;	// L332
    }
    int32_t ret[4];	// L334
    for (int v213 = 0; v213 < 4; v213++) {	// L335
      ret[v213] = 0;	// L335
    }
    l_S_d_3_d2: for (int d2 = 0; d2 < 4; d2++) {	// L336
      int32_t v215 = pop[d2];	// L337
      bool v216 = v215 == 1;	// L338
      if (v216) {	// L339
        l_S_sft_3_sft: for (int sft = 0; sft < 1; sft++) {	// L340
          ap_uint<26> v218 = rbuf[d2][(sft + 1)];	// L341
          rbuf[d2][sft] = v218;	// L342
        }
        int32_t v219 = rbcnt[d2];	// L344
        ap_int<33> v220 = v219;	// L345
        ap_int<33> v221 = v220 - 1;	// L346
        int32_t v222 = v221;	// L347
        rbcnt[d2] = v222;	// L348
        ret[d2] = 1;	// L349
      }
    }
    int32_t v223 = ret[0];	// L352
    cre_r = v223;	// L353
    int32_t v224 = ret[1];	// L354
    crw_r = v224;	// L355
    int32_t v225 = ret[2];	// L356
    crs_r = v225;	// L357
    int32_t v226 = ret[3];	// L358
    crn_r = v226;	// L359
    ap_uint<26> v227 = o_out[0];	// L360
    oe_r = v227;	// L361
    ap_uint<26> v228 = o_out[1];	// L362
    ow_r = v228;	// L363
    ap_uint<26> v229 = o_out[2];	// L364
    os_r = v229;	// L365
    ap_uint<26> v230 = o_out[3];	// L366
    on_r = v230;	// L367
    int32_t v231 = inj_done;	// L368
    bool v232 = v231 == 1;	// L369
    if (v232) {	// L370
      csd_pkt = 0;	// L371
    }
    ap_int<26> v233 = o_crv;	// L373
    bool v234;
    ap_int<26> v234_tmp = v233;
    v234 = v234_tmp[25];	// L374
    int32_t v235 = v234;	// L375
    crv_vld = v235;	// L376
    ap_int<26> v236 = o_crv;	// L377
    int16_t v237;
    ap_int<26> v237_tmp = v236;
    v237 = v237_tmp(15, 0);	// L378
    half v238;
    union { uint16_t from; half to;} _converter_v237_to_v238;
    _converter_v237_to_v238.from = v237;
    v238 = _converter_v237_to_v238.to;	// L379
    crv_data = v238;	// L380
    ap_int<26> v239 = o_crv;	// L381
    ap_int<4> v240;
    ap_int<26> v240_tmp = v239;
    v240 = v240_tmp(19, 16);	// L382
    int32_t v241 = v240;	// L383
    crv_addr = v241;	// L384
    ap_int<26> v242 = o_crv;	// L385
    bool v243;
    ap_int<26> v243_tmp = v242;
    v243 = v243_tmp[20];	// L386
    int32_t v244 = v243;	// L387
    crv_mode = v244;	// L388
    ap_int<26> v245 = o_crv;	// L389
    int16_t v246;
    ap_int<26> v246_tmp = v245;
    v246 = v246_tmp(15, 0);	// L390
    int32_t v247 = v246;	// L391
    crv_raw = v247;	// L392
    ap_uint<17> v248 = v20.read();	// L393
    ap_uint<17> rx_w;	// L394
    rx_w = v248;	// L395
    ap_uint<17> v250 = v21.read();	// L396
    ap_uint<17> rx_e;	// L397
    rx_e = v250;	// L398
    ap_uint<17> v252 = v22.read();	// L399
    ap_uint<17> rx_n;	// L400
    rx_n = v252;	// L401
    ap_uint<17> v254 = v23.read();	// L402
    ap_uint<17> rx_s;	// L403
    rx_s = v254;	// L404
    half rxv[4];	// L405
    for (int v257 = 0; v257 < 4; v257++) {	// L406
      rxv[v257] = (double)0.000000;	// L406
    }
    int32_t rxvld[4];	// L407
    for (int v259 = 0; v259 < 4; v259++) {	// L408
      rxvld[v259] = 0;	// L408
    }
    ap_int<17> v260 = rx_n;	// L409
    int16_t v261;
    ap_int<17> v261_tmp = v260;
    v261 = v261_tmp(16, 1);	// L410
    half v262;
    union { uint16_t from; half to;} _converter_v261_to_v262;
    _converter_v261_to_v262.from = v261;
    v262 = _converter_v261_to_v262.to;	// L411
    rxv[0] = v262;	// L412
    ap_int<17> v263 = rx_n;	// L413
    bool v264;
    ap_int<17> v264_tmp = v263;
    v264 = v264_tmp[0];	// L414
    int32_t v265 = v264;	// L415
    rxvld[0] = v265;	// L416
    ap_int<17> v266 = rx_s;	// L417
    int16_t v267;
    ap_int<17> v267_tmp = v266;
    v267 = v267_tmp(16, 1);	// L418
    half v268;
    union { uint16_t from; half to;} _converter_v267_to_v268;
    _converter_v267_to_v268.from = v267;
    v268 = _converter_v267_to_v268.to;	// L419
    rxv[1] = v268;	// L420
    ap_int<17> v269 = rx_s;	// L421
    bool v270;
    ap_int<17> v270_tmp = v269;
    v270 = v270_tmp[0];	// L422
    int32_t v271 = v270;	// L423
    rxvld[1] = v271;	// L424
    ap_int<17> v272 = rx_w;	// L425
    int16_t v273;
    ap_int<17> v273_tmp = v272;
    v273 = v273_tmp(16, 1);	// L426
    half v274;
    union { uint16_t from; half to;} _converter_v273_to_v274;
    _converter_v273_to_v274.from = v273;
    v274 = _converter_v273_to_v274.to;	// L427
    rxv[2] = v274;	// L428
    ap_int<17> v275 = rx_w;	// L429
    bool v276;
    ap_int<17> v276_tmp = v275;
    v276 = v276_tmp[0];	// L430
    int32_t v277 = v276;	// L431
    rxvld[2] = v277;	// L432
    ap_int<17> v278 = rx_e;	// L433
    int16_t v279;
    ap_int<17> v279_tmp = v278;
    v279 = v279_tmp(16, 1);	// L434
    half v280;
    union { uint16_t from; half to;} _converter_v279_to_v280;
    _converter_v279_to_v280.from = v279;
    v280 = _converter_v279_to_v280.to;	// L435
    rxv[3] = v280;	// L436
    ap_int<17> v281 = rx_e;	// L437
    bool v282;
    ap_int<17> v282_tmp = v281;
    v282 = v282_tmp[0];	// L438
    int32_t v283 = v282;	// L439
    rxvld[3] = v283;	// L440
    l_S_d_5_d3: for (int d3 = 0; d3 < 4; d3++) {	// L441
      int32_t v285 = rxvld[d3];	// L442
      bool v286 = v285 == 1;	// L443
      int32_t v287 = hold_cnt[d3];	// L444
      bool v288 = v287 < 2;	// L445
      bool v289 = v286 & v288;	// L446
      if (v289) {	// L447
        half v290 = rxv[d3];	// L448
        int32_t v291 = hold_cnt[d3];	// L449
        int v292 = v291;	// L450
        hold_v[d3][v292] = v290;	// L451
        int32_t v293 = hold_cnt[d3];	// L452
        ap_int<33> v294 = v293;	// L453
        ap_int<33> v295 = v294 + 1;	// L454
        int32_t v296 = v295;	// L455
        hold_cnt[d3] = v296;	// L456
      }
    }
    int32_t pc;	// L459
    pc = -1;	// L460
    int32_t v298 = fetch_en;	// L461
    bool v299 = v298 == 1;	// L462
    if (v299) {	// L463
      int32_t v300 = instr_cnt;	// L464
      pc = v300;	// L465
    }
    int32_t instr;	// L467
    instr = 0;	// L468
    int32_t v302 = pc;	// L469
    bool v303 = v302 >= 0;	// L470
    if (v303) {	// L471
      int32_t v304 = pc;	// L472
      int v305 = v304;	// L473
      int32_t v306 = irf[v305];	// L474
      instr = v306;	// L475
    }
    int32_t v307 = instr;	// L477
    int32_t v308 = v307 & 15;	// L478
    int32_t op;	// L479
    op = v308;	// L480
    int32_t v310 = instr;	// L481
    int32_t v311 = v310 >> 4;	// L482
    int32_t v312 = v311 & 15;	// L483
    int32_t dst;	// L484
    dst = v312;	// L485
    int32_t v314 = instr;	// L486
    int32_t v315 = v314 >> 8;	// L487
    int32_t v316 = v315 & 15;	// L488
    int32_t s1;	// L489
    s1 = v316;	// L490
    int32_t v318 = instr;	// L491
    int32_t v319 = v318 >> 12;	// L492
    int32_t v320 = v319 & 15;	// L493
    int32_t s2;	// L494
    s2 = v320;	// L495
    half a;	// L496
    a = (double)0.000000;	// L497
    half b;	// L498
    b = (double)0.000000;	// L499
    int32_t v324 = s1;	// L500
    bool v325 = v324 >= 12;	// L501
    if (v325) {	// L502
      int32_t v326 = s1;	// L503
      int32_t v327 = v326 & 3;	// L504
      int v328 = v327;	// L505
      half v329 = hold_v[v328][0];	// L506
      a = v329;	// L507
    } else {
      int32_t v330 = s1;	// L509
      int v331 = v330;	// L510
      half v332 = drf[v331];	// L511
      a = v332;	// L512
    }
    int32_t v333 = s2;	// L514
    bool v334 = v333 >= 12;	// L515
    if (v334) {	// L516
      int32_t v335 = s2;	// L517
      int32_t v336 = v335 & 3;	// L518
      int v337 = v336;	// L519
      half v338 = hold_v[v337][0];	// L520
      b = v338;	// L521
    } else {
      int32_t v339 = s2;	// L523
      int v340 = v339;	// L524
      half v341 = drf[v340];	// L525
      b = v341;	// L526
    }
    int32_t a_vld;	// L528
    a_vld = 1;	// L529
    int32_t b_vld;	// L530
    b_vld = 1;	// L531
    int32_t v344 = s1;	// L532
    bool v345 = v344 >= 12;	// L533
    if (v345) {	// L534
      a_vld = 0;	// L535
      int32_t v346 = s1;	// L536
      int32_t v347 = v346 & 3;	// L537
      int v348 = v347;	// L538
      int32_t v349 = hold_cnt[v348];	// L539
      bool v350 = v349 > 0;	// L540
      if (v350) {	// L541
        a_vld = 1;	// L542
      }
    }
    int32_t v351 = s2;	// L545
    bool v352 = v351 >= 12;	// L546
    if (v352) {	// L547
      b_vld = 0;	// L548
      int32_t v353 = s2;	// L549
      int32_t v354 = v353 & 3;	// L550
      int v355 = v354;	// L551
      int32_t v356 = hold_cnt[v355];	// L552
      bool v357 = v356 > 0;	// L553
      if (v357) {	// L554
        b_vld = 1;	// L555
      }
    }
    int32_t v358 = s1;	// L558
    bool v359 = v358 < 8;	// L559
    int32_t v360 = dsmask;	// L560
    int32_t v361 = v360 >> v358;	// L561
    int32_t v362 = v361 & 1;	// L562
    bool v363 = v362 == 1;	// L563
    bool v364 = v359 & v363;	// L564
    if (v364) {	// L565
      int32_t v365 = s1;	// L566
      int v366 = v365;	// L567
      int32_t v367 = drf_full[v366];	// L568
      bool v368 = v367 == 0;	// L569
      if (v368) {	// L570
        a_vld = 0;	// L571
      }
    }
    int32_t v369 = s2;	// L574
    bool v370 = v369 < 8;	// L575
    int32_t v371 = dsmask;	// L576
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
    bool v383 = v381 == 1;	// L594
    bool v384 = v381 == 2;	// L595
    bool v385 = v381 == 8;	// L596
    bool v386 = v381 == 9;	// L597
    bool v387 = v382 | v383;	// L598
    bool v388 = v387 | v384;	// L599
    bool v389 = v388 | v385;	// L600
    bool v390 = v389 | v386;	// L601
    if (v390) {	// L602
      binop = 1;	// L603
    }
    int32_t grant;	// L605
    grant = 0;	// L606
    int32_t v392 = pc;	// L607
    bool v393 = v392 >= 0;	// L608
    if (v393) {	// L609
      grant = 1;	// L610
    }
    int32_t v394 = pc;	// L612
    bool v395 = v394 >= 0;	// L613
    int32_t v396 = a_vld;	// L614
    bool v397 = v396 == 0;	// L615
    int32_t v398 = binop;	// L616
    bool v399 = v398 == 1;	// L617
    int32_t v400 = b_vld;	// L618
    bool v401 = v400 == 0;	// L619
    bool v402 = v399 & v401;	// L620
    bool v403 = v397 | v402;	// L621
    bool v404 = v395 & v403;	// L622
    if (v404) {	// L623
      grant = 0;	// L624
    }
    int32_t v405 = grant;	// L626
    bool v406 = v405 == 1;	// L627
    if (v406) {	// L628
      int32_t v407 = instr_cnt;	// L629
      int32_t v408 = cfg_isz;	// L630
      bool v409 = v407 == v408;	// L631
      if (v409) {	// L632
        instr_cnt = 0;	// L633
        int32_t v410 = iter_cnt;	// L634
        int32_t v411 = cfg_itsz;	// L635
        ap_int<33> v412 = v411;	// L636
        ap_int<33> v413 = v412 - 1;	// L637
        ap_int<33> v414 = v410;	// L638
        bool v415 = v414 == v413;	// L639
        if (v415) {	// L640
          fetch_en = 0;	// L641
        } else {
          int32_t v416 = iter_cnt;	// L643
          ap_int<33> v417 = v416;	// L644
          ap_int<33> v418 = v417 + 1;	// L645
          int32_t v419 = v418;	// L646
          iter_cnt = v419;	// L647
        }
      } else {
        int32_t v420 = instr_cnt;	// L650
        ap_int<33> v421 = v420;	// L651
        ap_int<33> v422 = v421 + 1;	// L652
        int32_t v423 = v422;	// L653
        instr_cnt = v423;	// L654
      }
    }
    int32_t c1;	// L657
    c1 = -1;	// L658
    int32_t c2;	// L659
    c2 = -1;	// L660
    int32_t v426 = grant;	// L661
    bool v427 = v426 == 1;	// L662
    int32_t v428 = s1;	// L663
    bool v429 = v428 >= 12;	// L664
    bool v430 = v427 & v429;	// L665
    if (v430) {	// L666
      int32_t v431 = s1;	// L667
      int32_t v432 = v431 & 3;	// L668
      c1 = v432;	// L669
    }
    int32_t v433 = grant;	// L671
    bool v434 = v433 == 1;	// L672
    int32_t v435 = s2;	// L673
    bool v436 = v435 >= 12;	// L674
    bool v437 = v434 & v436;	// L675
    if (v437) {	// L676
      int32_t v438 = s2;	// L677
      int32_t v439 = v438 & 3;	// L678
      c2 = v439;	// L679
    }
    int32_t v440 = c1;	// L681
    bool v441 = v440 >= 0;	// L682
    if (v441) {	// L683
      int32_t v442 = c1;	// L684
      int v443 = v442;	// L685
      half v444 = hold_v[v443][1];	// L686
      hold_v[v443][0] = v444;	// L687
      int32_t v445 = c1;	// L688
      int v446 = v445;	// L689
      int32_t v447 = hold_cnt[v446];	// L690
      ap_int<33> v448 = v447;	// L691
      ap_int<33> v449 = v448 - 1;	// L692
      int32_t v450 = v449;	// L693
      hold_cnt[v446] = v450;	// L694
    }
    int32_t v451 = c2;	// L696
    bool v452 = v451 >= 0;	// L697
    int32_t v453 = c1;	// L698
    bool v454 = v451 != v453;	// L699
    bool v455 = v452 & v454;	// L700
    if (v455) {	// L701
      int32_t v456 = c2;	// L702
      int v457 = v456;	// L703
      half v458 = hold_v[v457][1];	// L704
      hold_v[v457][0] = v458;	// L705
      int32_t v459 = c2;	// L706
      int v460 = v459;	// L707
      int32_t v461 = hold_cnt[v460];	// L708
      ap_int<33> v462 = v461;	// L709
      ap_int<33> v463 = v462 - 1;	// L710
      int32_t v464 = v463;	// L711
      hold_cnt[v460] = v464;	// L712
    }
    int32_t v465 = grant;	// L714
    bool v466 = v465 == 1;	// L715
    int32_t v467 = s1;	// L716
    bool v468 = v467 < 8;	// L717
    int32_t v469 = dsmask;	// L718
    int32_t v470 = v469 >> v467;	// L719
    int32_t v471 = v470 & 1;	// L720
    bool v472 = v471 == 1;	// L721
    bool v473 = v466 & v468;	// L722
    bool v474 = v473 & v472;	// L723
    if (v474) {	// L724
      int32_t v475 = s1;	// L725
      int v476 = v475;	// L726
      drf_full[v476] = 0;	// L727
    }
    int32_t v477 = grant;	// L729
    bool v478 = v477 == 1;	// L730
    int32_t v479 = s2;	// L731
    bool v480 = v479 < 8;	// L732
    int32_t v481 = dsmask;	// L733
    int32_t v482 = v481 >> v479;	// L734
    int32_t v483 = v482 & 1;	// L735
    bool v484 = v483 == 1;	// L736
    bool v485 = v478 & v480;	// L737
    bool v486 = v485 & v484;	// L738
    if (v486) {	// L739
      int32_t v487 = s2;	// L740
      int v488 = v487;	// L741
      drf_full[v488] = 0;	// L742
    }
    half res;	// L744
    res = (double)0.000000;	// L745
    int32_t v490 = op;	// L746
    bool v491 = v490 == 0;	// L747
    if (v491) {	// L748
      half v492 = a;	// L749
      half v493 = b;	// L750
      half v494 = v492 + v493;	// L751
      res = v494;	// L752
    } else {
      int32_t v495 = op;	// L754
      bool v496 = v495 == 1;	// L755
      if (v496) {	// L756
        half v497 = a;	// L757
        half v498 = b;	// L758
        half v499 = v497 - v498;	// L759
        res = v499;	// L760
      } else {
        int32_t v500 = op;	// L762
        bool v501 = v500 == 2;	// L763
        if (v501) {	// L764
          half v502 = a;	// L765
          half v503 = b;	// L766
          half v504 = v502 * v503;	// L767
          res = v504;	// L768
        } else {
          int32_t v505 = op;	// L770
          bool v506 = v505 == 8;	// L771
          if (v506) {	// L772
            half v507 = a;	// L773
            half v508 = b;	// L774
            bool v509 = v507 >= v508;	// L775
            if (v509) {	// L776
              res = (double)1.000000;	// L777
            } else {
              res = (double)-1.000000;	// L779
            }
          } else {
            int32_t v510 = op;	// L782
            bool v511 = v510 == 9;	// L783
            if (v511) {	// L784
              half v512 = a;	// L785
              half v513 = b;	// L786
              bool v514 = v512 < v513;	// L787
              if (v514) {	// L788
                res = (double)1.000000;	// L789
              } else {
                res = (double)-1.000000;	// L791
              }
            } else {
              half v515 = a;	// L794
              res = v515;	// L795
            }
          }
        }
      }
    }
    int32_t v516 = a_vld;	// L801
    int32_t res_vld;	// L802
    res_vld = v516;	// L803
    int32_t v518 = op;	// L804
    bool v519 = v518 == 0;	// L805
    bool v520 = v518 == 1;	// L806
    bool v521 = v518 == 2;	// L807
    bool v522 = v518 == 8;	// L808
    bool v523 = v518 == 9;	// L809
    bool v524 = v519 | v520;	// L810
    bool v525 = v524 | v521;	// L811
    bool v526 = v525 | v522;	// L812
    bool v527 = v526 | v523;	// L813
    if (v527) {	// L814
      int32_t v528 = a_vld;	// L815
      int32_t v529 = b_vld;	// L816
      int64_t v530 = v528;	// L817
      int64_t v531 = v529;	// L818
      int64_t v532 = v530 * v531;	// L819
      int32_t v533 = v532;	// L820
      res_vld = v533;	// L821
    }
    int32_t v534 = grant;	// L823
    bool v535 = v534 == 0;	// L824
    if (v535) {	// L825
      res_vld = 0;	// L826
    }
    int32_t v536 = grant;	// L828
    bool v537 = v536 == 1;	// L829
    int32_t v538 = op;	// L830
    bool v539 = v538 == 8;	// L831
    bool v540 = v537 & v539;	// L832
    if (v540) {	// L833
      condition_reg = 0;	// L834
      half v541 = a;	// L835
      half v542 = b;	// L836
      bool v543 = v541 >= v542;	// L837
      if (v543) {	// L838
        condition_reg = 1;	// L839
      }
    }
    int32_t v544 = grant;	// L842
    bool v545 = v544 == 1;	// L843
    int32_t v546 = op;	// L844
    bool v547 = v546 == 9;	// L845
    bool v548 = v545 & v547;	// L846
    if (v548) {	// L847
      condition_reg = 0;	// L848
      half v549 = a;	// L849
      half v550 = b;	// L850
      bool v551 = v549 < v550;	// L851
      if (v551) {	// L852
        condition_reg = 1;	// L853
      }
    }
    ap_uint<17> tx_n;	// L856
    tx_n = 0;	// L857
    ap_uint<17> tx_s;	// L858
    tx_s = 0;	// L859
    ap_uint<17> tx_w;	// L860
    tx_w = 0;	// L861
    ap_uint<17> tx_e;	// L862
    tx_e = 0;	// L863
    int32_t is_rtr;	// L864
    is_rtr = 0;	// L865
    int32_t do_inj;	// L866
    do_inj = 0;	// L867
    int32_t v558 = op;	// L868
    bool v559 = v558 >= 4;	// L869
    ap_int<33> v560 = v558;	// L870
    bool v561 = v560 <= 7;	// L871
    bool v562 = v559 & v561;	// L872
    if (v562) {	// L873
      is_rtr = 1;	// L874
      do_inj = 1;	// L875
    }
    int32_t v563 = op;	// L877
    bool v564 = v563 >= 12;	// L878
    ap_int<33> v565 = v563;	// L879
    bool v566 = v565 <= 15;	// L880
    bool v567 = v564 & v566;	// L881
    if (v567) {	// L882
      is_rtr = 1;	// L883
      int32_t v568 = condition_reg;	// L884
      bool v569 = v568 == 1;	// L885
      if (v569) {	// L886
        do_inj = 1;	// L887
      }
    }
    int32_t v570 = is_rtr;	// L890
    bool v571 = v570 == 1;	// L891
    if (v571) {	// L892
      int32_t v572 = do_inj;	// L893
      bool v573 = v572 == 1;	// L894
      ap_int<26> v574 = csd_pkt;	// L895
      bool v575;
      ap_int<26> v575_tmp = v574;
      v575 = v575_tmp[25];	// L896
      int32_t v576 = v575;	// L897
      bool v577 = v576 == 0;	// L898
      bool v578 = v573 & v577;	// L899
      if (v578) {	// L900
        half v579 = res;	// L901
        uint16_t v580;
        union { half from; uint16_t to;} _converter_v579_to_v580;
        _converter_v579_to_v580.from = v579;
        v580 = _converter_v579_to_v580.to;	// L902
        ap_int<26> v581 = csd_pkt;	// L903
        ap_int<26> v582;
        ap_int<26> v582_tmp = v581;
        v582_tmp(15, 0) = v580;
        v582 = v582_tmp;	// L904
        csd_pkt = v582;	// L905
        int32_t v583 = dst;	// L906
        ap_uint<4> v584 = v583;	// L907
        ap_int<26> v585 = csd_pkt;	// L908
        ap_int<26> v586;
        ap_int<26> v586_tmp = v585;
        v586_tmp(19, 16) = v584;
        v586 = v586_tmp;	// L909
        csd_pkt = v586;	// L910
        int32_t v587 = s2;	// L911
        ap_uint<4> v588 = v587;	// L912
        ap_int<26> v589 = csd_pkt;	// L913
        ap_int<26> v590;
        ap_int<26> v590_tmp = v589;
        v590_tmp(24, 21) = v588;
        v590 = v590_tmp;	// L914
        csd_pkt = v590;	// L915
        int32_t v591 = res_vld;	// L916
        bool v592 = v591;	// L917
        ap_int<26> v593 = csd_pkt;	// L918
        ap_int<26> v594;
        ap_int<26> v594_tmp = v593;
        v594_tmp[25] = v592;        v594 = v594_tmp;	// L919
        csd_pkt = v594;	// L920
        int32_t v595 = op;	// L921
        int32_t v596 = v595 & 3;	// L922
        csd_dir = v596;	// L923
      }
    } else {
      int32_t v597 = dst;	// L926
      bool v598 = v597 >= 12;	// L927
      if (v598) {	// L928
        ap_uint<17> tw;	// L929
        tw = 0;	// L930
        int32_t v600 = res_vld;	// L931
        bool v601 = v600;	// L932
        ap_int<17> v602 = tw;	// L933
        ap_int<17> v603;
        ap_int<17> v603_tmp = v602;
        v603_tmp[0] = v601;        v603 = v603_tmp;	// L934
        tw = v603;	// L935
        half v604 = res;	// L936
        uint16_t v605;
        union { half from; uint16_t to;} _converter_v604_to_v605;
        _converter_v604_to_v605.from = v604;
        v605 = _converter_v604_to_v605.to;	// L937
        ap_int<17> v606 = tw;	// L938
        ap_int<17> v607;
        ap_int<17> v607_tmp = v606;
        v607_tmp(16, 1) = v605;
        v607 = v607_tmp;	// L939
        tw = v607;	// L940
        int32_t v608 = dst;	// L941
        int32_t v609 = v608 & 3;	// L942
        bool v610 = v609 == 0;	// L943
        if (v610) {	// L944
          ap_int<17> v611 = tw;	// L945
          tx_n = v611;	// L946
        } else {
          int32_t v612 = dst;	// L948
          int32_t v613 = v612 & 3;	// L949
          bool v614 = v613 == 1;	// L950
          if (v614) {	// L951
            ap_int<17> v615 = tw;	// L952
            tx_s = v615;	// L953
          } else {
            int32_t v616 = dst;	// L955
            int32_t v617 = v616 & 3;	// L956
            bool v618 = v617 == 2;	// L957
            if (v618) {	// L958
              ap_int<17> v619 = tw;	// L959
              tx_w = v619;	// L960
            } else {
              ap_int<17> v620 = tw;	// L962
              tx_e = v620;	// L963
            }
          }
        }
      } else {
        int32_t v621 = res_vld;	// L968
        bool v622 = v621 == 1;	// L969
        if (v622) {	// L970
          int32_t v623 = dst;	// L971
          bool v624 = v623 < 8;	// L972
          int32_t v625 = dsmask;	// L973
          int32_t v626 = v625 >> v623;	// L974
          int32_t v627 = v626 & 1;	// L975
          bool v628 = v627 == 1;	// L976
          bool v629 = v624 & v628;	// L977
          if (v629) {	// L978
            int32_t v630 = dst;	// L979
            int v631 = v630;	// L980
            int32_t v632 = drf_full[v631];	// L981
            bool v633 = v632 == 0;	// L982
            if (v633) {	// L983
              half v634 = res;	// L984
              int32_t v635 = dst;	// L985
              int v636 = v635;	// L986
              drf[v636] = v634;	// L987
              int32_t v637 = dst;	// L988
              int v638 = v637;	// L989
              drf_full[v638] = 1;	// L990
            }
          } else {
            half v639 = res;	// L993
            int32_t v640 = dst;	// L994
            int v641 = v640;	// L995
            drf[v641] = v639;	// L996
          }
        }
      }
    }
    ap_int<17> v642 = tx_n;	// L1001
    txn_r = v642;	// L1002
    ap_int<17> v643 = tx_s;	// L1003
    txs_r = v643;	// L1004
    ap_int<17> v644 = tx_w;	// L1005
    txw_r = v644;	// L1006
    ap_int<17> v645 = tx_e;	// L1007
    txe_r = v645;	// L1008
    int32_t v646 = crv_vld;	// L1009
    bool v647 = v646 == 1;	// L1010
    if (v647) {	// L1011
      int32_t v648 = crv_mode;	// L1012
      bool v649 = v648 == 1;	// L1013
      if (v649) {	// L1014
        int32_t v650 = crv_addr;	// L1015
        int32_t v651 = v650 >> 3;	// L1016
        int32_t v652 = v651 & 1;	// L1017
        bool v653 = v652 == 1;	// L1018
        if (v653) {	// L1019
          int32_t v654 = crv_raw;	// L1020
          int32_t v655 = crv_addr;	// L1021
          int32_t v656 = v655 & 7;	// L1022
          int v657 = v656;	// L1023
          irf[v657] = v654;	// L1024
        } else {
          int32_t v658 = crv_addr;	// L1026
          bool v659 = v658 == 0;	// L1027
          if (v659) {	// L1028
            int32_t v660 = crv_raw;	// L1029
            int32_t v661 = v660 & 255;	// L1030
            dsmask = v661;	// L1031
            int32_t v662 = crv_raw;	// L1032
            int32_t v663 = v662 >> 8;	// L1033
            int32_t v664 = v663 & 7;	// L1034
            cfg_isz = v664;	// L1035
            int32_t v665 = crv_raw;	// L1036
            int32_t v666 = v665 >> 15;	// L1037
            int32_t v667 = v666 & 1;	// L1038
            bool v668 = v667 == 1;	// L1039
            if (v668) {	// L1040
              fetch_en = 1;	// L1041
              instr_cnt = 0;	// L1042
              iter_cnt = 0;	// L1043
            }
          } else {
            int32_t v669 = crv_addr;	// L1046
            bool v670 = v669 == 1;	// L1047
            if (v670) {	// L1048
              int32_t v671 = crv_raw;	// L1049
              int32_t v672 = v671 & 255;	// L1050
              cfg_itsz = v672;	// L1051
            }
          }
        }
      } else {
        int32_t v673 = crv_addr;	// L1056
        bool v674 = v673 < 8;	// L1057
        int32_t v675 = dsmask;	// L1058
        int32_t v676 = v675 >> v673;	// L1059
        int32_t v677 = v676 & 1;	// L1060
        bool v678 = v677 == 1;	// L1061
        bool v679 = v674 & v678;	// L1062
        if (v679) {	// L1063
          int32_t v680 = crv_addr;	// L1064
          int v681 = v680;	// L1065
          int32_t v682 = drf_full[v681];	// L1066
          bool v683 = v682 == 0;	// L1067
          if (v683) {	// L1068
            half v684 = crv_data;	// L1069
            int32_t v685 = crv_addr;	// L1070
            int v686 = v685;	// L1071
            drf[v686] = v684;	// L1072
            int32_t v687 = crv_addr;	// L1073
            int v688 = v687;	// L1074
            drf_full[v688] = 1;	// L1075
          }
        } else {
          half v689 = crv_data;	// L1078
          int32_t v690 = crv_addr;	// L1079
          int v691 = v690;	// L1080
          drf[v691] = v689;	// L1081
        }
      }
    }
    ap_int<26> v692 = oe_r;	// L1085
    v0.write(v692);	// L1086
    ap_int<26> v693 = ow_r;	// L1087
    v1.write(v693);	// L1088
    ap_int<26> v694 = os_r;	// L1089
    v2.write(v694);	// L1090
    ap_int<26> v695 = on_r;	// L1091
    v3.write(v695);	// L1092
    ap_int<17> v696 = txe_r;	// L1093
    v4.write(v696);	// L1094
    ap_int<17> v697 = txw_r;	// L1095
    v5.write(v697);	// L1096
    ap_int<17> v698 = txs_r;	// L1097
    v6.write(v698);	// L1098
    ap_int<17> v699 = txn_r;	// L1099
    v7.write(v699);	// L1100
    int32_t v700 = cre_r;	// L1101
    v8.write(v700);	// L1102
    int32_t v701 = crw_r;	// L1103
    v9.write(v701);	// L1104
    int32_t v702 = crs_r;	// L1105
    v10.write(v702);	// L1106
    int32_t v703 = crn_r;	// L1107
    v11.write(v703);	// L1108
  }
}

void drv_w_0(
  half v704[1][10],
  int32_t v705[1][10],
  hls::stream< ap_uint<17> >& v706
) {	// L1112
  l_S_t_0_t1: for (int t1 = 0; t1 < 10; t1++) {	// L1118
    ap_uint<17> w;	// L1119
    w = 0;	// L1120
    ap_int<33> v709 = t1;	// L1121
    bool v710 = v709 < 10;	// L1122
    if (v710) {	// L1123
      int32_t v711 = v705[0][t1];	// L1124
      bool v712 = v711;	// L1125
      ap_int<17> v713 = w;	// L1126
      ap_int<17> v714;
      ap_int<17> v714_tmp = v713;
      v714_tmp[0] = v712;      v714 = v714_tmp;	// L1127
      w = v714;	// L1128
      half v715 = v704[0][t1];	// L1129
      uint16_t v716;
      union { half from; uint16_t to;} _converter_v715_to_v716;
      _converter_v715_to_v716.from = v715;
      v716 = _converter_v715_to_v716.to;	// L1130
      ap_int<17> v717 = w;	// L1131
      ap_int<17> v718;
      ap_int<17> v718_tmp = v717;
      v718_tmp(16, 1) = v716;
      v718 = v718_tmp;	// L1132
      w = v718;	// L1133
    }
    ap_int<17> v719 = w;	// L1135
    v706.write(v719);	// L1136
  }
}

void drv_e_0(
  half v720[1][10],
  int32_t v721[1][10],
  hls::stream< ap_uint<17> >& v722
) {	// L1140
  l_S_t_0_t2: for (int t2 = 0; t2 < 10; t2++) {	// L1146
    ap_uint<17> w1;	// L1147
    w1 = 0;	// L1148
    ap_int<33> v725 = t2;	// L1149
    bool v726 = v725 < 10;	// L1150
    if (v726) {	// L1151
      int32_t v727 = v721[0][t2];	// L1152
      bool v728 = v727;	// L1153
      ap_int<17> v729 = w1;	// L1154
      ap_int<17> v730;
      ap_int<17> v730_tmp = v729;
      v730_tmp[0] = v728;      v730 = v730_tmp;	// L1155
      w1 = v730;	// L1156
      half v731 = v720[0][t2];	// L1157
      uint16_t v732;
      union { half from; uint16_t to;} _converter_v731_to_v732;
      _converter_v731_to_v732.from = v731;
      v732 = _converter_v731_to_v732.to;	// L1158
      ap_int<17> v733 = w1;	// L1159
      ap_int<17> v734;
      ap_int<17> v734_tmp = v733;
      v734_tmp(16, 1) = v732;
      v734 = v734_tmp;	// L1160
      w1 = v734;	// L1161
    }
    ap_int<17> v735 = w1;	// L1163
    v722.write(v735);	// L1164
  }
}

void drv_n_0(
  half v736[1][10],
  int32_t v737[1][10],
  hls::stream< ap_uint<17> >& v738
) {	// L1168
  l_S_t_0_t3: for (int t3 = 0; t3 < 10; t3++) {	// L1174
    ap_uint<17> w2;	// L1175
    w2 = 0;	// L1176
    ap_int<33> v741 = t3;	// L1177
    bool v742 = v741 < 10;	// L1178
    if (v742) {	// L1179
      int32_t v743 = v737[0][t3];	// L1180
      bool v744 = v743;	// L1181
      ap_int<17> v745 = w2;	// L1182
      ap_int<17> v746;
      ap_int<17> v746_tmp = v745;
      v746_tmp[0] = v744;      v746 = v746_tmp;	// L1183
      w2 = v746;	// L1184
      half v747 = v736[0][t3];	// L1185
      uint16_t v748;
      union { half from; uint16_t to;} _converter_v747_to_v748;
      _converter_v747_to_v748.from = v747;
      v748 = _converter_v747_to_v748.to;	// L1186
      ap_int<17> v749 = w2;	// L1187
      ap_int<17> v750;
      ap_int<17> v750_tmp = v749;
      v750_tmp(16, 1) = v748;
      v750 = v750_tmp;	// L1188
      w2 = v750;	// L1189
    }
    ap_int<17> v751 = w2;	// L1191
    v738.write(v751);	// L1192
  }
}

void drv_s_0(
  half v752[1][10],
  int32_t v753[1][10],
  hls::stream< ap_uint<17> >& v754
) {	// L1196
  l_S_t_0_t4: for (int t4 = 0; t4 < 10; t4++) {	// L1202
    ap_uint<17> w3;	// L1203
    w3 = 0;	// L1204
    ap_int<33> v757 = t4;	// L1205
    bool v758 = v757 < 10;	// L1206
    if (v758) {	// L1207
      int32_t v759 = v753[0][t4];	// L1208
      bool v760 = v759;	// L1209
      ap_int<17> v761 = w3;	// L1210
      ap_int<17> v762;
      ap_int<17> v762_tmp = v761;
      v762_tmp[0] = v760;      v762 = v762_tmp;	// L1211
      w3 = v762;	// L1212
      half v763 = v752[0][t4];	// L1213
      uint16_t v764;
      union { half from; uint16_t to;} _converter_v763_to_v764;
      _converter_v763_to_v764.from = v763;
      v764 = _converter_v763_to_v764.to;	// L1214
      ap_int<17> v765 = w3;	// L1215
      ap_int<17> v766;
      ap_int<17> v766_tmp = v765;
      v766_tmp(16, 1) = v764;
      v766 = v766_tmp;	// L1216
      w3 = v766;	// L1217
    }
    ap_int<17> v767 = w3;	// L1219
    v754.write(v767);	// L1220
  }
}

void col_w_0(
  half v768[1][10],
  hls::stream< ap_uint<17> >& v769
) {	// L1224
  int32_t k[1];	// L1232
  for (int v771 = 0; v771 < 1; v771++) {	// L1233
    k[v771] = 0;	// L1233
  }
  l_S_t_0_t5: for (int t5 = 0; t5 < 10; t5++) {	// L1234
    ap_uint<17> v773 = v769.read();	// L1235
    ap_uint<17> w4;	// L1236
    w4 = v773;	// L1237
    ap_int<17> v775 = w4;	// L1238
    bool v776;
    ap_int<17> v776_tmp = v775;
    v776 = v776_tmp[0];	// L1239
    int32_t v777 = v776;	// L1240
    bool v778 = v777 == 1;	// L1241
    int32_t v779 = k[0];	// L1242
    bool v780 = v779 < 10;	// L1243
    bool v781 = v778 & v780;	// L1244
    if (v781) {	// L1245
      ap_int<17> v782 = w4;	// L1246
      int16_t v783;
      ap_int<17> v783_tmp = v782;
      v783 = v783_tmp(16, 1);	// L1247
      half v784;
      union { uint16_t from; half to;} _converter_v783_to_v784;
      _converter_v783_to_v784.from = v783;
      v784 = _converter_v783_to_v784.to;	// L1248
      int32_t v785 = k[0];	// L1249
      int v786 = v785;	// L1250
      v768[0][v786] = v784;	// L1251
      int32_t v787 = k[0];	// L1252
      ap_int<33> v788 = v787;	// L1253
      ap_int<33> v789 = v788 + 1;	// L1254
      int32_t v790 = v789;	// L1255
      k[0] = v790;	// L1256
    }
  }
}

void col_e_0(
  half v791[1][10],
  hls::stream< ap_uint<17> >& v792
) {	// L1261
  int32_t k1[1];	// L1269
  for (int v794 = 0; v794 < 1; v794++) {	// L1270
    k1[v794] = 0;	// L1270
  }
  l_S_t_0_t6: for (int t6 = 0; t6 < 10; t6++) {	// L1271
    ap_uint<17> v796 = v792.read();	// L1272
    ap_uint<17> w5;	// L1273
    w5 = v796;	// L1274
    ap_int<17> v798 = w5;	// L1275
    bool v799;
    ap_int<17> v799_tmp = v798;
    v799 = v799_tmp[0];	// L1276
    int32_t v800 = v799;	// L1277
    bool v801 = v800 == 1;	// L1278
    int32_t v802 = k1[0];	// L1279
    bool v803 = v802 < 10;	// L1280
    bool v804 = v801 & v803;	// L1281
    if (v804) {	// L1282
      ap_int<17> v805 = w5;	// L1283
      int16_t v806;
      ap_int<17> v806_tmp = v805;
      v806 = v806_tmp(16, 1);	// L1284
      half v807;
      union { uint16_t from; half to;} _converter_v806_to_v807;
      _converter_v806_to_v807.from = v806;
      v807 = _converter_v806_to_v807.to;	// L1285
      int32_t v808 = k1[0];	// L1286
      int v809 = v808;	// L1287
      v791[0][v809] = v807;	// L1288
      int32_t v810 = k1[0];	// L1289
      ap_int<33> v811 = v810;	// L1290
      ap_int<33> v812 = v811 + 1;	// L1291
      int32_t v813 = v812;	// L1292
      k1[0] = v813;	// L1293
    }
  }
}

void col_n_0(
  half v814[1][10],
  hls::stream< ap_uint<17> >& v815
) {	// L1298
  int32_t k2[1];	// L1306
  for (int v817 = 0; v817 < 1; v817++) {	// L1307
    k2[v817] = 0;	// L1307
  }
  l_S_t_0_t7: for (int t7 = 0; t7 < 10; t7++) {	// L1308
    ap_uint<17> v819 = v815.read();	// L1309
    ap_uint<17> w6;	// L1310
    w6 = v819;	// L1311
    ap_int<17> v821 = w6;	// L1312
    bool v822;
    ap_int<17> v822_tmp = v821;
    v822 = v822_tmp[0];	// L1313
    int32_t v823 = v822;	// L1314
    bool v824 = v823 == 1;	// L1315
    int32_t v825 = k2[0];	// L1316
    bool v826 = v825 < 10;	// L1317
    bool v827 = v824 & v826;	// L1318
    if (v827) {	// L1319
      ap_int<17> v828 = w6;	// L1320
      int16_t v829;
      ap_int<17> v829_tmp = v828;
      v829 = v829_tmp(16, 1);	// L1321
      half v830;
      union { uint16_t from; half to;} _converter_v829_to_v830;
      _converter_v829_to_v830.from = v829;
      v830 = _converter_v829_to_v830.to;	// L1322
      int32_t v831 = k2[0];	// L1323
      int v832 = v831;	// L1324
      v814[0][v832] = v830;	// L1325
      int32_t v833 = k2[0];	// L1326
      ap_int<33> v834 = v833;	// L1327
      ap_int<33> v835 = v834 + 1;	// L1328
      int32_t v836 = v835;	// L1329
      k2[0] = v836;	// L1330
    }
  }
}

void col_s_0(
  half v837[1][10],
  hls::stream< ap_uint<17> >& v838
) {	// L1335
  int32_t k3[1];	// L1343
  for (int v840 = 0; v840 < 1; v840++) {	// L1344
    k3[v840] = 0;	// L1344
  }
  l_S_t_0_t8: for (int t8 = 0; t8 < 10; t8++) {	// L1345
    ap_uint<17> v842 = v838.read();	// L1346
    ap_uint<17> w7;	// L1347
    w7 = v842;	// L1348
    ap_int<17> v844 = w7;	// L1349
    bool v845;
    ap_int<17> v845_tmp = v844;
    v845 = v845_tmp[0];	// L1350
    int32_t v846 = v845;	// L1351
    bool v847 = v846 == 1;	// L1352
    int32_t v848 = k3[0];	// L1353
    bool v849 = v848 < 10;	// L1354
    bool v850 = v847 & v849;	// L1355
    if (v850) {	// L1356
      ap_int<17> v851 = w7;	// L1357
      int16_t v852;
      ap_int<17> v852_tmp = v851;
      v852 = v852_tmp(16, 1);	// L1358
      half v853;
      union { uint16_t from; half to;} _converter_v852_to_v853;
      _converter_v852_to_v853.from = v852;
      v853 = _converter_v852_to_v853.to;	// L1359
      int32_t v854 = k3[0];	// L1360
      int v855 = v854;	// L1361
      v837[0][v855] = v853;	// L1362
      int32_t v856 = k3[0];	// L1363
      ap_int<33> v857 = v856;	// L1364
      ap_int<33> v858 = v857 + 1;	// L1365
      int32_t v859 = v858;	// L1366
      k3[0] = v859;	// L1367
    }
  }
}

void rdrv_w_0(
  int32_t v860[1][10],
  hls::stream< int32_t >& v861,
  hls::stream< ap_uint<26> >& v862
) {	// L1372
  int32_t dcred[1];	// L1379
  for (int v864 = 0; v864 < 1; v864++) {	// L1380
    dcred[v864] = 0;	// L1380
  }
  int32_t sp[1];	// L1381
  for (int v866 = 0; v866 < 1; v866++) {	// L1382
    sp[v866] = 0;	// L1382
  }
  l_S_t_0_t9: for (int t9 = 0; t9 < 10; t9++) {	// L1383
    int32_t v868 = v861.read();	// L1384
    int32_t v869 = dcred[0];	// L1385
    ap_int<33> v870 = v869;	// L1386
    ap_int<33> v871 = v868;	// L1387
    ap_int<33> v872 = v870 + v871;	// L1388
    int32_t v873 = v872;	// L1389
    dcred[0] = v873;	// L1390
    ap_uint<26> pw;	// L1391
    pw = 0;	// L1392
    int32_t v875 = sp[0];	// L1393
    bool v876 = v875 < 10;	// L1394
    if (v876) {	// L1395
      ap_uint<26> cand;	// L1396
      cand = 0;	// L1397
      int32_t v878 = sp[0];	// L1398
      int v879 = v878;	// L1399
      int32_t v880 = v860[0][v879];	// L1400
      ap_uint<26> v881 = v880;	// L1401
      ap_int<26> v882 = cand;	// L1402
      ap_int<26> v883;
      ap_int<26> v883_tmp = v882;
      v883_tmp(25, 0) = v881;
      v883 = v883_tmp;	// L1403
      cand = v883;	// L1404
      ap_int<26> v884 = cand;	// L1405
      bool v885;
      ap_int<26> v885_tmp = v884;
      v885 = v885_tmp[25];	// L1406
      int32_t v886 = v885;	// L1407
      bool v887 = v886 == 0;	// L1408
      if (v887) {	// L1409
        int32_t v888 = sp[0];	// L1410
        ap_int<33> v889 = v888;	// L1411
        ap_int<33> v890 = v889 + 1;	// L1412
        int32_t v891 = v890;	// L1413
        sp[0] = v891;	// L1414
      } else {
        int32_t v892 = dcred[0];	// L1416
        bool v893 = v892 > 0;	// L1417
        if (v893) {	// L1418
          ap_int<26> v894 = cand;	// L1419
          pw = v894;	// L1420
          int32_t v895 = dcred[0];	// L1421
          ap_int<33> v896 = v895;	// L1422
          ap_int<33> v897 = v896 - 1;	// L1423
          int32_t v898 = v897;	// L1424
          dcred[0] = v898;	// L1425
          int32_t v899 = sp[0];	// L1426
          ap_int<33> v900 = v899;	// L1427
          ap_int<33> v901 = v900 + 1;	// L1428
          int32_t v902 = v901;	// L1429
          sp[0] = v902;	// L1430
        }
      }
    }
    ap_int<26> v903 = pw;	// L1434
    v862.write(v903);	// L1435
  }
}

void rdrv_e_0(
  int32_t v904[1][10],
  hls::stream< int32_t >& v905,
  hls::stream< ap_uint<26> >& v906
) {	// L1439
  int32_t dcred1[1];	// L1446
  for (int v908 = 0; v908 < 1; v908++) {	// L1447
    dcred1[v908] = 0;	// L1447
  }
  int32_t sp1[1];	// L1448
  for (int v910 = 0; v910 < 1; v910++) {	// L1449
    sp1[v910] = 0;	// L1449
  }
  l_S_t_0_t10: for (int t10 = 0; t10 < 10; t10++) {	// L1450
    int32_t v912 = v905.read();	// L1451
    int32_t v913 = dcred1[0];	// L1452
    ap_int<33> v914 = v913;	// L1453
    ap_int<33> v915 = v912;	// L1454
    ap_int<33> v916 = v914 + v915;	// L1455
    int32_t v917 = v916;	// L1456
    dcred1[0] = v917;	// L1457
    ap_uint<26> pw1;	// L1458
    pw1 = 0;	// L1459
    int32_t v919 = sp1[0];	// L1460
    bool v920 = v919 < 10;	// L1461
    if (v920) {	// L1462
      ap_uint<26> cand1;	// L1463
      cand1 = 0;	// L1464
      int32_t v922 = sp1[0];	// L1465
      int v923 = v922;	// L1466
      int32_t v924 = v904[0][v923];	// L1467
      ap_uint<26> v925 = v924;	// L1468
      ap_int<26> v926 = cand1;	// L1469
      ap_int<26> v927;
      ap_int<26> v927_tmp = v926;
      v927_tmp(25, 0) = v925;
      v927 = v927_tmp;	// L1470
      cand1 = v927;	// L1471
      ap_int<26> v928 = cand1;	// L1472
      bool v929;
      ap_int<26> v929_tmp = v928;
      v929 = v929_tmp[25];	// L1473
      int32_t v930 = v929;	// L1474
      bool v931 = v930 == 0;	// L1475
      if (v931) {	// L1476
        int32_t v932 = sp1[0];	// L1477
        ap_int<33> v933 = v932;	// L1478
        ap_int<33> v934 = v933 + 1;	// L1479
        int32_t v935 = v934;	// L1480
        sp1[0] = v935;	// L1481
      } else {
        int32_t v936 = dcred1[0];	// L1483
        bool v937 = v936 > 0;	// L1484
        if (v937) {	// L1485
          ap_int<26> v938 = cand1;	// L1486
          pw1 = v938;	// L1487
          int32_t v939 = dcred1[0];	// L1488
          ap_int<33> v940 = v939;	// L1489
          ap_int<33> v941 = v940 - 1;	// L1490
          int32_t v942 = v941;	// L1491
          dcred1[0] = v942;	// L1492
          int32_t v943 = sp1[0];	// L1493
          ap_int<33> v944 = v943;	// L1494
          ap_int<33> v945 = v944 + 1;	// L1495
          int32_t v946 = v945;	// L1496
          sp1[0] = v946;	// L1497
        }
      }
    }
    ap_int<26> v947 = pw1;	// L1501
    v906.write(v947);	// L1502
  }
}

void rdrv_n_0(
  int32_t v948[1][10],
  hls::stream< int32_t >& v949,
  hls::stream< ap_uint<26> >& v950
) {	// L1506
  int32_t dcred2[1];	// L1513
  for (int v952 = 0; v952 < 1; v952++) {	// L1514
    dcred2[v952] = 0;	// L1514
  }
  int32_t sp2[1];	// L1515
  for (int v954 = 0; v954 < 1; v954++) {	// L1516
    sp2[v954] = 0;	// L1516
  }
  l_S_t_0_t11: for (int t11 = 0; t11 < 10; t11++) {	// L1517
    int32_t v956 = v949.read();	// L1518
    int32_t v957 = dcred2[0];	// L1519
    ap_int<33> v958 = v957;	// L1520
    ap_int<33> v959 = v956;	// L1521
    ap_int<33> v960 = v958 + v959;	// L1522
    int32_t v961 = v960;	// L1523
    dcred2[0] = v961;	// L1524
    ap_uint<26> pw2;	// L1525
    pw2 = 0;	// L1526
    int32_t v963 = sp2[0];	// L1527
    bool v964 = v963 < 10;	// L1528
    if (v964) {	// L1529
      ap_uint<26> cand2;	// L1530
      cand2 = 0;	// L1531
      int32_t v966 = sp2[0];	// L1532
      int v967 = v966;	// L1533
      int32_t v968 = v948[0][v967];	// L1534
      ap_uint<26> v969 = v968;	// L1535
      ap_int<26> v970 = cand2;	// L1536
      ap_int<26> v971;
      ap_int<26> v971_tmp = v970;
      v971_tmp(25, 0) = v969;
      v971 = v971_tmp;	// L1537
      cand2 = v971;	// L1538
      ap_int<26> v972 = cand2;	// L1539
      bool v973;
      ap_int<26> v973_tmp = v972;
      v973 = v973_tmp[25];	// L1540
      int32_t v974 = v973;	// L1541
      bool v975 = v974 == 0;	// L1542
      if (v975) {	// L1543
        int32_t v976 = sp2[0];	// L1544
        ap_int<33> v977 = v976;	// L1545
        ap_int<33> v978 = v977 + 1;	// L1546
        int32_t v979 = v978;	// L1547
        sp2[0] = v979;	// L1548
      } else {
        int32_t v980 = dcred2[0];	// L1550
        bool v981 = v980 > 0;	// L1551
        if (v981) {	// L1552
          ap_int<26> v982 = cand2;	// L1553
          pw2 = v982;	// L1554
          int32_t v983 = dcred2[0];	// L1555
          ap_int<33> v984 = v983;	// L1556
          ap_int<33> v985 = v984 - 1;	// L1557
          int32_t v986 = v985;	// L1558
          dcred2[0] = v986;	// L1559
          int32_t v987 = sp2[0];	// L1560
          ap_int<33> v988 = v987;	// L1561
          ap_int<33> v989 = v988 + 1;	// L1562
          int32_t v990 = v989;	// L1563
          sp2[0] = v990;	// L1564
        }
      }
    }
    ap_int<26> v991 = pw2;	// L1568
    v950.write(v991);	// L1569
  }
}

void rdrv_s_0(
  int32_t v992[1][10],
  hls::stream< int32_t >& v993,
  hls::stream< ap_uint<26> >& v994
) {	// L1573
  int32_t dcred3[1];	// L1580
  for (int v996 = 0; v996 < 1; v996++) {	// L1581
    dcred3[v996] = 0;	// L1581
  }
  int32_t sp3[1];	// L1582
  for (int v998 = 0; v998 < 1; v998++) {	// L1583
    sp3[v998] = 0;	// L1583
  }
  l_S_t_0_t12: for (int t12 = 0; t12 < 10; t12++) {	// L1584
    int32_t v1000 = v993.read();	// L1585
    int32_t v1001 = dcred3[0];	// L1586
    ap_int<33> v1002 = v1001;	// L1587
    ap_int<33> v1003 = v1000;	// L1588
    ap_int<33> v1004 = v1002 + v1003;	// L1589
    int32_t v1005 = v1004;	// L1590
    dcred3[0] = v1005;	// L1591
    ap_uint<26> pw3;	// L1592
    pw3 = 0;	// L1593
    int32_t v1007 = sp3[0];	// L1594
    bool v1008 = v1007 < 10;	// L1595
    if (v1008) {	// L1596
      ap_uint<26> cand3;	// L1597
      cand3 = 0;	// L1598
      int32_t v1010 = sp3[0];	// L1599
      int v1011 = v1010;	// L1600
      int32_t v1012 = v992[0][v1011];	// L1601
      ap_uint<26> v1013 = v1012;	// L1602
      ap_int<26> v1014 = cand3;	// L1603
      ap_int<26> v1015;
      ap_int<26> v1015_tmp = v1014;
      v1015_tmp(25, 0) = v1013;
      v1015 = v1015_tmp;	// L1604
      cand3 = v1015;	// L1605
      ap_int<26> v1016 = cand3;	// L1606
      bool v1017;
      ap_int<26> v1017_tmp = v1016;
      v1017 = v1017_tmp[25];	// L1607
      int32_t v1018 = v1017;	// L1608
      bool v1019 = v1018 == 0;	// L1609
      if (v1019) {	// L1610
        int32_t v1020 = sp3[0];	// L1611
        ap_int<33> v1021 = v1020;	// L1612
        ap_int<33> v1022 = v1021 + 1;	// L1613
        int32_t v1023 = v1022;	// L1614
        sp3[0] = v1023;	// L1615
      } else {
        int32_t v1024 = dcred3[0];	// L1617
        bool v1025 = v1024 > 0;	// L1618
        if (v1025) {	// L1619
          ap_int<26> v1026 = cand3;	// L1620
          pw3 = v1026;	// L1621
          int32_t v1027 = dcred3[0];	// L1622
          ap_int<33> v1028 = v1027;	// L1623
          ap_int<33> v1029 = v1028 - 1;	// L1624
          int32_t v1030 = v1029;	// L1625
          dcred3[0] = v1030;	// L1626
          int32_t v1031 = sp3[0];	// L1627
          ap_int<33> v1032 = v1031;	// L1628
          ap_int<33> v1033 = v1032 + 1;	// L1629
          int32_t v1034 = v1033;	// L1630
          sp3[0] = v1034;	// L1631
        }
      }
    }
    ap_int<26> v1035 = pw3;	// L1635
    v994.write(v1035);	// L1636
  }
}

void rclc_w_0(
  int32_t v1036[1][10],
  hls::stream< int32_t >& v1037,
  hls::stream< ap_uint<26> >& v1038
) {	// L1640
  int32_t k4[1];	// L1649
  for (int v1040 = 0; v1040 < 1; v1040++) {	// L1650
    k4[v1040] = 0;	// L1650
  }
  int32_t cret[1];	// L1651
  for (int v1042 = 0; v1042 < 1; v1042++) {	// L1652
    cret[v1042] = 0;	// L1652
  }
  cret[0] = 2;	// L1653
  int32_t v1043 = cret[0];	// L1654
  v1037.write(v1043);	// L1655
  l_S_t_0_t13: for (int t13 = 0; t13 < 10; t13++) {	// L1656
    ap_uint<26> v1045 = v1038.read();	// L1657
    ap_uint<26> pw4;	// L1658
    pw4 = v1045;	// L1659
    cret[0] = 0;	// L1660
    ap_int<26> v1047 = pw4;	// L1661
    bool v1048;
    ap_int<26> v1048_tmp = v1047;
    v1048 = v1048_tmp[25];	// L1662
    int32_t v1049 = v1048;	// L1663
    bool v1050 = v1049 == 1;	// L1664
    if (v1050) {	// L1665
      cret[0] = 1;	// L1666
      int32_t v1051 = k4[0];	// L1667
      bool v1052 = v1051 < 10;	// L1668
      if (v1052) {	// L1669
        ap_int<26> v1053 = pw4;	// L1670
        int32_t v1054 = v1053;	// L1671
        int32_t v1055 = v1054 & 67108863;	// L1672
        int32_t v1056 = k4[0];	// L1673
        int v1057 = v1056;	// L1674
        v1036[0][v1057] = v1055;	// L1675
        int32_t v1058 = k4[0];	// L1676
        ap_int<33> v1059 = v1058;	// L1677
        ap_int<33> v1060 = v1059 + 1;	// L1678
        int32_t v1061 = v1060;	// L1679
        k4[0] = v1061;	// L1680
      }
    }
    int32_t v1062 = cret[0];	// L1683
    v1037.write(v1062);	// L1684
  }
}

void rclc_e_0(
  int32_t v1063[1][10],
  hls::stream< int32_t >& v1064,
  hls::stream< ap_uint<26> >& v1065
) {	// L1688
  int32_t k5[1];	// L1697
  for (int v1067 = 0; v1067 < 1; v1067++) {	// L1698
    k5[v1067] = 0;	// L1698
  }
  int32_t cret1[1];	// L1699
  for (int v1069 = 0; v1069 < 1; v1069++) {	// L1700
    cret1[v1069] = 0;	// L1700
  }
  cret1[0] = 2;	// L1701
  int32_t v1070 = cret1[0];	// L1702
  v1064.write(v1070);	// L1703
  l_S_t_0_t14: for (int t14 = 0; t14 < 10; t14++) {	// L1704
    ap_uint<26> v1072 = v1065.read();	// L1705
    ap_uint<26> pw5;	// L1706
    pw5 = v1072;	// L1707
    cret1[0] = 0;	// L1708
    ap_int<26> v1074 = pw5;	// L1709
    bool v1075;
    ap_int<26> v1075_tmp = v1074;
    v1075 = v1075_tmp[25];	// L1710
    int32_t v1076 = v1075;	// L1711
    bool v1077 = v1076 == 1;	// L1712
    if (v1077) {	// L1713
      cret1[0] = 1;	// L1714
      int32_t v1078 = k5[0];	// L1715
      bool v1079 = v1078 < 10;	// L1716
      if (v1079) {	// L1717
        ap_int<26> v1080 = pw5;	// L1718
        int32_t v1081 = v1080;	// L1719
        int32_t v1082 = v1081 & 67108863;	// L1720
        int32_t v1083 = k5[0];	// L1721
        int v1084 = v1083;	// L1722
        v1063[0][v1084] = v1082;	// L1723
        int32_t v1085 = k5[0];	// L1724
        ap_int<33> v1086 = v1085;	// L1725
        ap_int<33> v1087 = v1086 + 1;	// L1726
        int32_t v1088 = v1087;	// L1727
        k5[0] = v1088;	// L1728
      }
    }
    int32_t v1089 = cret1[0];	// L1731
    v1064.write(v1089);	// L1732
  }
}

void rclc_n_0(
  int32_t v1090[1][10],
  hls::stream< int32_t >& v1091,
  hls::stream< ap_uint<26> >& v1092
) {	// L1736
  int32_t k6[1];	// L1745
  for (int v1094 = 0; v1094 < 1; v1094++) {	// L1746
    k6[v1094] = 0;	// L1746
  }
  int32_t cret2[1];	// L1747
  for (int v1096 = 0; v1096 < 1; v1096++) {	// L1748
    cret2[v1096] = 0;	// L1748
  }
  cret2[0] = 2;	// L1749
  int32_t v1097 = cret2[0];	// L1750
  v1091.write(v1097);	// L1751
  l_S_t_0_t15: for (int t15 = 0; t15 < 10; t15++) {	// L1752
    ap_uint<26> v1099 = v1092.read();	// L1753
    ap_uint<26> pw6;	// L1754
    pw6 = v1099;	// L1755
    cret2[0] = 0;	// L1756
    ap_int<26> v1101 = pw6;	// L1757
    bool v1102;
    ap_int<26> v1102_tmp = v1101;
    v1102 = v1102_tmp[25];	// L1758
    int32_t v1103 = v1102;	// L1759
    bool v1104 = v1103 == 1;	// L1760
    if (v1104) {	// L1761
      cret2[0] = 1;	// L1762
      int32_t v1105 = k6[0];	// L1763
      bool v1106 = v1105 < 10;	// L1764
      if (v1106) {	// L1765
        ap_int<26> v1107 = pw6;	// L1766
        int32_t v1108 = v1107;	// L1767
        int32_t v1109 = v1108 & 67108863;	// L1768
        int32_t v1110 = k6[0];	// L1769
        int v1111 = v1110;	// L1770
        v1090[0][v1111] = v1109;	// L1771
        int32_t v1112 = k6[0];	// L1772
        ap_int<33> v1113 = v1112;	// L1773
        ap_int<33> v1114 = v1113 + 1;	// L1774
        int32_t v1115 = v1114;	// L1775
        k6[0] = v1115;	// L1776
      }
    }
    int32_t v1116 = cret2[0];	// L1779
    v1091.write(v1116);	// L1780
  }
}

void rclc_s_0(
  int32_t v1117[1][10],
  hls::stream< int32_t >& v1118,
  hls::stream< ap_uint<26> >& v1119
) {	// L1784
  int32_t k7[1];	// L1793
  for (int v1121 = 0; v1121 < 1; v1121++) {	// L1794
    k7[v1121] = 0;	// L1794
  }
  int32_t cret3[1];	// L1795
  for (int v1123 = 0; v1123 < 1; v1123++) {	// L1796
    cret3[v1123] = 0;	// L1796
  }
  cret3[0] = 2;	// L1797
  int32_t v1124 = cret3[0];	// L1798
  v1118.write(v1124);	// L1799
  l_S_t_0_t16: for (int t16 = 0; t16 < 10; t16++) {	// L1800
    ap_uint<26> v1126 = v1119.read();	// L1801
    ap_uint<26> pw7;	// L1802
    pw7 = v1126;	// L1803
    cret3[0] = 0;	// L1804
    ap_int<26> v1128 = pw7;	// L1805
    bool v1129;
    ap_int<26> v1129_tmp = v1128;
    v1129 = v1129_tmp[25];	// L1806
    int32_t v1130 = v1129;	// L1807
    bool v1131 = v1130 == 1;	// L1808
    if (v1131) {	// L1809
      cret3[0] = 1;	// L1810
      int32_t v1132 = k7[0];	// L1811
      bool v1133 = v1132 < 10;	// L1812
      if (v1133) {	// L1813
        ap_int<26> v1134 = pw7;	// L1814
        int32_t v1135 = v1134;	// L1815
        int32_t v1136 = v1135 & 67108863;	// L1816
        int32_t v1137 = k7[0];	// L1817
        int v1138 = v1137;	// L1818
        v1117[0][v1138] = v1136;	// L1819
        int32_t v1139 = k7[0];	// L1820
        ap_int<33> v1140 = v1139;	// L1821
        ap_int<33> v1141 = v1140 + 1;	// L1822
        int32_t v1142 = v1141;	// L1823
        k7[0] = v1142;	// L1824
      }
    }
    int32_t v1143 = cret3[0];	// L1827
    v1118.write(v1143);	// L1828
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
) {	// L1832
  #pragma HLS dataflow
  hls::stream< ap_uint<17> > v1164;
  #pragma HLS stream variable=v1164 depth=2	// L1833
  hls::stream< ap_uint<17> > v1165;
  #pragma HLS stream variable=v1165 depth=2	// L1834
  hls::stream< ap_uint<17> > v1166;
  #pragma HLS stream variable=v1166 depth=2	// L1835
  hls::stream< ap_uint<17> > v1167;
  #pragma HLS stream variable=v1167 depth=2	// L1836
  hls::stream< ap_uint<17> > v1168;
  #pragma HLS stream variable=v1168 depth=2	// L1837
  hls::stream< ap_uint<17> > v1169;
  #pragma HLS stream variable=v1169 depth=2	// L1838
  hls::stream< ap_uint<17> > v1170;
  #pragma HLS stream variable=v1170 depth=2	// L1839
  hls::stream< ap_uint<17> > v1171;
  #pragma HLS stream variable=v1171 depth=2	// L1840
  hls::stream< ap_uint<26> > v1172;
  #pragma HLS stream variable=v1172 depth=2	// L1841
  hls::stream< ap_uint<26> > v1173;
  #pragma HLS stream variable=v1173 depth=2	// L1842
  hls::stream< ap_uint<26> > v1174;
  #pragma HLS stream variable=v1174 depth=2	// L1843
  hls::stream< ap_uint<26> > v1175;
  #pragma HLS stream variable=v1175 depth=2	// L1844
  hls::stream< ap_uint<26> > v1176;
  #pragma HLS stream variable=v1176 depth=2	// L1845
  hls::stream< ap_uint<26> > v1177;
  #pragma HLS stream variable=v1177 depth=2	// L1846
  hls::stream< ap_uint<26> > v1178;
  #pragma HLS stream variable=v1178 depth=2	// L1847
  hls::stream< ap_uint<26> > v1179;
  #pragma HLS stream variable=v1179 depth=2	// L1848
  hls::stream< int32_t > v1180;
  #pragma HLS stream variable=v1180 depth=2	// L1849
  hls::stream< int32_t > v1181;
  #pragma HLS stream variable=v1181 depth=2	// L1850
  hls::stream< int32_t > v1182;
  #pragma HLS stream variable=v1182 depth=2	// L1851
  hls::stream< int32_t > v1183;
  #pragma HLS stream variable=v1183 depth=2	// L1852
  hls::stream< int32_t > v1184;
  #pragma HLS stream variable=v1184 depth=2	// L1853
  hls::stream< int32_t > v1185;
  #pragma HLS stream variable=v1185 depth=2	// L1854
  hls::stream< int32_t > v1186;
  #pragma HLS stream variable=v1186 depth=2	// L1855
  hls::stream< int32_t > v1187;
  #pragma HLS stream variable=v1187 depth=2	// L1856
  node_0_0(v1173, v1174, v1177, v1178, v1165, v1166, v1169, v1170, v1180, v1183, v1184, v1187, v1172, v1175, v1176, v1179, v1181, v1182, v1185, v1186, v1164, v1167, v1168, v1171);	// L1857
  drv_w_0(v1144, v1145, v1164);	// L1858
  drv_e_0(v1146, v1147, v1167);	// L1859
  drv_n_0(v1148, v1149, v1168);	// L1860
  drv_s_0(v1150, v1151, v1171);	// L1861
  col_w_0(v1152, v1166);	// L1862
  col_e_0(v1153, v1165);	// L1863
  col_n_0(v1154, v1170);	// L1864
  col_s_0(v1155, v1169);	// L1865
  rdrv_w_0(v1156, v1180, v1172);	// L1866
  rdrv_e_0(v1157, v1183, v1175);	// L1867
  rdrv_n_0(v1158, v1184, v1176);	// L1868
  rdrv_s_0(v1159, v1187, v1179);	// L1869
  rclc_w_0(v1160, v1182, v1174);	// L1870
  rclc_e_0(v1161, v1181, v1173);	// L1871
  rclc_n_0(v1162, v1186, v1178);	// L1872
  rclc_s_0(v1163, v1185, v1177);	// L1873
}

